#include "test_function_base.h"

namespace test_function {

class Rosenbrock : public TestFunction {
public:
    Rosenbrock(double a=1.0, double b=100.0);
    double value(const Eigen::VectorXd& x) const;
    Eigen::VectorXd gradient(const Eigen::VectorXd& x) const;
    Eigen::MatrixXd hessian(const Eigen::VectorXd& x) const;

private:
    double a_;
    double b_;
};

}