#!/usr/bin/env python

import numpy as np
import numpy.ma as ma
import sys;
import numpy.random as ra


# ----------------------------------------------------------------------------
## Model for IDEAL fat-water separation
# Has functions to compute the system matrices A and B
# as well as intermediate least squares result u
class IDEAL:
    ## Constructor
    #@param data numpy array holding sample points of complex fat water signal
    #@param te numpy array of sampling times (echo times)
    def __init__(self, data, te):
        self.te = te;
        self.omega = 0;
        self.data = data;
        
        # fat offset frequency
        freq = 460;
        self.freq = 460;
        
        # fat coefficients
        self.c1n = np.cos(2*np.pi*freq*te);
        self.d1n = np.sin(2*np.pi*freq*te);
        
        # water coefficients
        self.c2n = np.ones(len(time));
        self.d2n = np.zeros(len(time));
        
        self.fresh = 0;
        self.deltaomega = 0;
        
        # vector to hold results of first least squares solution
        self.u = np.zeros(4);
        
        # data prepared as vector for least squares optimization
        self.signalvec = np.concatenate((signal.real, signal.imag),axis=0);
    
    ## Returns Least Squares Matrix A
    #@return 4x6 numpy matrix for first least squares step
    def getA(self):
        A = np.concatenate((self.c1n, self.d1n, -self.d1n, self.c1n, self.c2n, self.d2n, -self.d2n, self.c2n),axis=0)
        A.shape = (4,6);
        A = A.T;
        return A;
    
    ## Returns Least Squares Matrix B
    #@return 5x6 numpy matrix for second least squares step
    def getB(self):
        gr = 2*np.pi*self.te*(-self.u[0]*self.d1n - self.u[1]*self.c1n - self.u[2]*self.d2n - self.u[3]*self.c2n)
        gi = 2*np.pi*self.te*( self.u[0]*self.c1n - self.u[1]*self.d1n + self.u[2]*self.c2n - self.u[3]*self.d2n) 
        
        C = np.concatenate((gr, gi, self.c1n, self.d1n, -self.d1n, self.c1n, self.c2n, self.d2n, -self.d2n, self.c2n),axis=0)
        C.shape = (5,6);
        C = C.T;
        return C;
    
    ## Returns delta omega of last iteration
    #@return delta omega
    def getDeltaOmega(self):
        return self.deltaomega;
    
    ## Sets the intermediate result u, real and imaginary parts of fat and water signal
    #@param u numpy array (1x4)
    def setU(self, u):
        self.u = u;
        self.fresh = 1;
        
    ## Update field map at end of iteration
    #@param v numpy array (1x5)
    def updateOmega(self, v):
        self.omega += v[0];
        self.deltaomega = v[0];
        omegafact = np.exp(2*np.pi*1j*self.omega*self.te);
        dummyr = v[1]*self.c1n - v[2]*self.d1n + v[3]*self.c2n - v[4]*self.d2n;
        dummyi = v[1]*self.d1n + v[2]*self.c1n + v[3]*self.d2n + v[4]*self.c2n;
        #self.data += dummyr + 1j*dummyi;
        self.data = self.data / omegafact;
        self.signalvec = np.concatenate((self.data.real, self.data.imag),axis=0);
    
    def getSignalVector(self):
        return self.signalvec;
        
    def getSignalVector2(self):
        dummyr =np.array(self.u[0]*self.c1n-self.u[1]*self.d1n+self.u[2]*self.c2n - self.u[3]*self.d2n);
        dummyi =np.array(self.u[0]*self.d1n+self.u[1]*self.c1n+self.u[2]*self.d2n + self.u[3]*self.c2n);
        return  self.signalvec - np.concatenate((dummyr, dummyi));
    

# ----------------------------------------------------------------------------
## Class for least squares optimization of IDEAL data
class IDEALOptimizer:
    ## Constructor
    #@param idealmodel IDEAL model object
    def __init__(self, idealmodel):
        self.ideal = idealmodel;
        self.iterationcount = 0;
    
    ## Function to start least squares optimization 
    def optimize(self):
        
        while (ideal.fresh == 0 or ideal.getDeltaOmega() > 0.6):
            
            A = self.ideal.getA();
            data = self.ideal.getSignalVector();
            u = np.linalg.lstsq(A, data)[0];
        
            self.ideal.setU(u);
        
            B = self.ideal.getB()
            data = self.ideal.getSignalVector2();
            v = np.linalg.lstsq(B,data)[0];
        
            v[1:len(v)] += u;
        
            self.ideal.updateOmega(v);
            self.iterationcount += 1;
    
        self.result = v[1:len(v)];
        self.omega = self.ideal.omega;

        
    

# ----------------------------------------------------------------------------


if __name__ == '__main__':
    
    # create test signal ==========================================
    time = np.array([1, 3, 5])*0.001
    print time
    freq = 460;
    omega = 2*np.pi*460;
    fat = 23.4*np.exp(1j*time*omega)
    water = 10.05*np.ones(len(time));
    signal = (fat + water)*np.exp(1j*2*np.pi*10*time);
    print(signal)
    signal += (ra.random(3) + ra.random(3)*1j) *0.0;
    
    # reconstruction ============================================= 
    ideal = IDEAL(signal, time);

    while (ideal.fresh == 0 or ideal.getDeltaOmega() > 0.6):
        A = ideal.getA();
        data = ideal.getSignalVector();
        u = np.linalg.lstsq(A, data)[0];
        
        ideal.setU(u);
        
        B = ideal.getB()
        data = ideal.getSignalVector2();
        v = np.linalg.lstsq(B,data)[0];
        
        v[1:len(v)] += u;
        
        ideal.updateOmega(v);
    
    # Print results ================================================
    np.set_printoptions(suppress=True,precision=2)
    print "RESULT:"
    print "coefficients: %s" % np.array_str(v)
    print "omega: %s" % np.array_str(ideal.omega)
    
    ideal = IDEAL(signal, time);
    optim = IDEALOptimizer(ideal);
    optim.optimize();
    
    print optim.result
    print optim.omega
    
    
    
    
    
    
    
    
    ##############################################################
    ##############################################################
    sys.exit();
    
    b= [];
    a = np.array([1.0, 1.0, 100.0, 1.0, 200.0, 3.0, 400.0, 30.0])
    a.shape = (2,4)
    b = ma.array(a, mask = [a[0] <= 3, a[0] < 3])
    print a[0]
    print a
    print b
    print a > 3.0
    print b.shape
    
    res = ma.array(np.zeros(b.shape),mask = b.mask)
    it = np.nditer([b[~b.mask], None])
    print "Bmask:"
    print b[~b.mask]
    
    count = 0
    for i,o in it:
        print i
        o[...] = i * 2;
        count +=1

    res[~res.mask] = it.operands[1];
    print res
    print b
    
    