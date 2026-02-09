#ifndef FIXED_STEP_SIZE_H
#define FIXED_STEP_SIZE_H

#include "step_size_base.h"

namespace numerical_optimization::step_size {

class FixedStepSize : public StepSizeStrategy {
public:
    FixedStepSize(double stepSize);

    double findStepSize(
        const Eigen::VectorXd& x, const Eigen::VectorXd& p,
        const test_function::TestFunction& f
    ) const;

private:
    double stepSize_;
};

}

#endif