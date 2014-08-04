#include "lmconfig.h"


namespace mrifit {
namespace cl {


const float LMConfig::TOL_PARAM = 1.0e-6;
const float LMConfig::TOL_CHI_SQUARE = 1.0e-5;
const float LMConfig::TOL_GRAD = 1.0e-6;
const float LMConfig::ACCEPT_LM_STEP = 1.0e-2;
const float LMConfig::DAMPING_LAMBDA = 1.0e-2;
const float LMConfig::INC_FACT_LAMBDA = 11.0;
const float LMConfig::DEC_FACT_LAMBDA = 9.0;
const unsigned int LMConfig::MAX_ITER = 100;


LMConfig::LMConfig() :
    tolParam_(TOL_PARAM),
    tolChiSquare_(TOL_CHI_SQUARE),
    tolGrad_(TOL_GRAD),
    acceptLMStep_(ACCEPT_LM_STEP),
    dampingLambda_(DAMPING_LAMBDA),
    incFactLambda_(INC_FACT_LAMBDA),
    decFactLambda_(DEC_FACT_LAMBDA),
    maxIter_(MAX_ITER)
{
}

LMConfig::~LMConfig()
{

}


void LMConfig::tolParam(float f)
{
    tolParam_ = f;
}

float LMConfig::tolParam() const
{
    return tolParam_;
}


void LMConfig::tolChiSquare(float f)
{
    tolChiSquare_ = f;
}

float LMConfig::tolChiSquare() const
{
    return tolChiSquare_;
}

void LMConfig::tolGrad(float f)
{
    tolGrad_ = f;
}

float LMConfig::tolGrad() const
{
    return tolGrad_;
}


void LMConfig::acceptLMStep(float f)
{
    acceptLMStep_ = f;
}

float LMConfig::acceptLMStep() const
{
    return acceptLMStep_;
}


void LMConfig::dampingLambda(float f)
{
    dampingLambda_ = f;
}

float LMConfig::dampingLambda() const
{
    return dampingLambda_;
}


void LMConfig::incFactLambda(float f)
{
    incFactLambda_ = f;
}

float LMConfig::incFactLambda() const
{
    return incFactLambda_;
}


void LMConfig::decFactLambda(float f)
{
    decFactLambda_ = f;
}

float LMConfig::decFactLambda() const
{
    return decFactLambda_;
}

void LMConfig::maxIter(unsigned int i)
{
    maxIter_ = i;
}

unsigned int LMConfig::maxIter() const
{
    return maxIter_;
}



}
}
