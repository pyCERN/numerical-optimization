#ifndef TEST_FUNCTION_BASE_H
#define TEST_FUNCTION_BASE_H

#include <Eigen/Dense>

namespace numerical_optimization::test_function {

class TestFunction {
public:
    virtual ~TestFunction() = default;

    virtual double value(const Eigen::VectorXd& x) const = 0;
    virtual Eigen::VectorXd gradient(const Eigen::VectorXd& x) const = 0;
    virtual Eigen::MatrixXd hessian(const Eigen::VectorXd& x) const = 0;
};

}

#endif