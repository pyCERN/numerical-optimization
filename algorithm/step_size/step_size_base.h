#ifndef STEP_SIZE_BASE_H
#define STEP_SIZE_BASE_H

#include <Eigen/Dense>

namespace numerical_optimization::test_function {
    class TestFunction;
}

namespace numerical_optimization::step_size {

class StepSizeStrategy {
public:
    virtual ~StepSizeStrategy() = default;

    virtual double findStepSize(
        const Eigen::VectorXd& x, const Eigen::VectorXd& p,
        const test_function::TestFunction& f
    ) const = 0;
};

}

#endif