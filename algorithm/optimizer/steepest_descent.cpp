#include "steepest_descent.h"
#include "../step_size/wolfe_search.h"
#include "../../test_functions/test_function_base.h"
#include <cmath>
#include <numeric>

namespace numerical_optimization::optimizer {

SteepestDescent::SteepestDescent(double stepSize, double tol, int maxIter)
    : stepSize_(stepSize), tol_(tol), maxIter_(maxIter)
{}

void SteepestDescent::optimize(
    const Eigen::VectorXd& x0,
    const test_function::TestFunction& f
) {
    Eigen::VectorXd x { std::move(x0) };
    result_.addHistory(x);

    for (int iter = 0; iter < maxIter_; iter++) {
        Eigen::VectorXd g = f.gradient(x);
        if (g.norm() < tol_) break;

        Eigen::VectorXd p = -g;
        x += stepSize_ * p;
        result_.addHistory(x);
    }

    result_.setSolution(x);
}

}