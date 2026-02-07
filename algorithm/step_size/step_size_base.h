#ifndef STEP_SIZE_BASE_H
#define STEP_SIZE_BASE_H

#include <Eigen/Dense>

namespace numerical_optimization::test_function {
    class TestFunction;
}

namespace numerical_optimization::step_size {

class StepSizeStrategy {
public:
    StepSizeStrategy(
        const Eigen::VectorXd& x, const Eigen::VectorXd& p,
        const test_function::TestFunction& f
    ) : x_(x), p_(p), f_(f)
    {}

    virtual ~StepSizeStrategy() = default;

    virtual double findStepSize() const = 0;

protected:
    Eigen::VectorXd x_; // current position
    Eigen::VectorXd p_; // direction
    const test_function::TestFunction& f_;
};

}

#endif