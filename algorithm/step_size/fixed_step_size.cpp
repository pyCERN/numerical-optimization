#include "fixed_step_size.h"
#include "../../test_functions/test_function_base.h"
#include <cmath>

namespace numerical_optimization::step_size {

FixedStepSize::FixedStepSize(double stepSize)
    : stepSize_(stepSize)
{}

double FixedStepSize::findStepSize(
    const Eigen::VectorXd& x, const Eigen::VectorXd& p,
    const test_function::TestFunction& f
) const {
    return stepSize_;
}

}