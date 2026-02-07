#include "newton.h"
#include "../step_size/wolfe_search.h"
#include "../../test_functions/test_function_base.h"
#include <cmath>
#include <numeric>

namespace numerical_optimization::optimizer {

Newton::Newton(double stepSize, double tol, int maxIter)
    : stepSize_(stepSize), tol_(tol), maxIter_(maxIter)
{}

void Newton::optimize(
    const Eigen::VectorXd& x0,
    const test_function::TestFunction& f
) {
    Eigen::VectorXd x = std::move(x0);
    result_.addHistory(x);

    for (int iter = 0; iter < maxIter_; iter++) {
        Eigen::VectorXd g = f.gradient(x);
        if (g.norm() < tol_) break;

        Eigen::MatrixXd hess = f.hessian(x);
        Eigen::VectorXd p = -hess.ldlt().solve(g);
        step_size::WolfeSearch stepSizeFinder(x, p, f, 1e-4, 0.9, 10000, 10000, 10.0, 2.0);
        double stepSize = stepSizeFinder.findStepSize();
        if (stepSize <= 0.0) break;

        x += stepSize * p;
        result_.addHistory(x);
    }

    result_.setSolution(x);
}

}