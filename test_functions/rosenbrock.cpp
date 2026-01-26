#include "rosenbrock.h"
#include <cmath>

namespace test_function {

Rosenbrock::Rosenbrock(double a, double b) : a_(a), b_(b)
{}

double Rosenbrock::value(const Eigen::VectorXd& x) const {
    return std::pow(a_ - x(0), 2) + b_ * std::pow((x(1) - std::pow(x(0), 2)), 2);
}

Eigen::VectorXd Rosenbrock::gradient(const Eigen::VectorXd& x) const {
    Eigen::VectorXd g(2);
    g(0) = -2 * (a_ - x(0)) - 4*b_*x(0) * (x(1) - std::pow(x(0), 2));
    g(1) = 2*b_ * (x(1) - std::pow(x(0), 2));
    return g;
}

Eigen::MatrixXd Rosenbrock::hessian(const Eigen::VectorXd& x) const {
    Eigen::MatrixXd h(2, 2);
    h(0, 0) = 2 - 4*b_*x(1) + 12*b_ * std::pow(x(1), 2);
    h(0, 1) = -4*b_*x(0);
    h(1, 0) = -4*b_*x(0);
    h(1, 1) = 2*b_;
    return h;
}
    
}