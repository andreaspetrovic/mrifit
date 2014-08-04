#ifndef LMCONFIG_H
#define LMCONFIG_H


namespace mrifit {
namespace cl {

/*!
 * \brief LMConfig stores parameters for the Levenberq-Marquardt algorithm
 * (as implemented by Sirk [Add Reference]). This class only exists of getters and
 * setters for the stored parameters.
 * \ingroup group_configloader
 */
class LMConfig
{
public:
    LMConfig();
    ~LMConfig();
    // getters and setters
    void tolParam(float f);
    float tolParam() const;
    void tolChiSquare(float f);
    float tolChiSquare() const;
    void tolGrad(float f);
    float tolGrad() const;
    void acceptLMStep(float f);
    float acceptLMStep() const;
    void dampingLambda(float f);
    float dampingLambda() const;
    void incFactLambda(float f);
    float incFactLambda() const;
    void decFactLambda(float f);
    float decFactLambda() const;
    void maxIter(unsigned int i);
    unsigned int maxIter() const;

    /// Default value for the parameter tolerance. The optimizer is stopped when ... (The one who know please document here!)
    static const float TOL_PARAM;
    /// (The one who knows please document here!)
    static const float TOL_CHI_SQUARE;
    /// (The one who knows please document here!)
    static const float TOL_GRAD;
    /// (The one who knows please document here!)
    static const float ACCEPT_LM_STEP;
    /// (The one who knows please document here!)
    static const float DAMPING_LAMBDA;
    /// (The one who knows please document here!)
    static const float INC_FACT_LAMBDA;
    /// (The one who knows please document here!)
    static const float DEC_FACT_LAMBDA;
    /// Default value for maximum number of iterations
    static const unsigned int MAX_ITER;

private:
    float tolParam_; /// test
    float tolChiSquare_;
    float tolGrad_;
    float acceptLMStep_;
    float dampingLambda_;
    float incFactLambda_;
    float decFactLambda_;
    unsigned int maxIter_;
};

}
}

#endif // LMCONFIG_H
