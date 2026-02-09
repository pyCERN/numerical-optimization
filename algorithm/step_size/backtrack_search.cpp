#include "backtrack_search.h"
#include "../../test_functions/test_function_base.h"
#include <cmath>

namespace numerical_optimization::step_size {

BacktrackSearch::BacktrackSearch(
    double c,
    double rho,
    int maxIter
) : c_(c), rho_(rho), maxIter_(maxIter)
{}

double BacktrackSearch::findStepSize(
    const Eigen::VectorXd& x, const Eigen::VectorXd& p,
    const test_function::TestFunction& f
) const {
    double stepSize = 1.0;
    for (int i = 0; i < maxIter_; i++) {
        if (f.value(x + stepSize*p) <= f.value(x) + c_*stepSize*f.gradient(x).dot(p)) {
            // Armijo condition satisfied.
            break;
        }
        stepSize *= rho_;
    }
    return stepSize;
}

}