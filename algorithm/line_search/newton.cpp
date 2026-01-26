#include "newton.h"
#include "../../test_functions/test_function_base.h"
#include <cmath>
#include <numeric>

namespace optimizer {

Newton::Newton(double alpha, double tol, int maxIter)
    : alpha_(alpha), tol_(tol), maxIter_(maxIter)
{}

void Newton::optimize(
    const Eigen::VectorXd& x0,
    const test_function::TestFunction& f
) {
    Eigen::VectorXd x { std::move(x0) };
    history_.push_back(x);

    for (int iter = 0; iter < maxIter_; iter++) {
        Eigen::VectorXd g { f.gradient(x) };
        if (g.norm() < tol_) break;

        Eigen::MatrixXd hess { f.hessian(x) };
        x -= alpha_ * hess.ldlt().solve(g);
        history_.push_back(x);
    }

    result_ = x;
}

}