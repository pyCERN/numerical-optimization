#include <Eigen/Dense>

namespace test_function {

class TestFunction {
public:
    virtual ~TestFunction() = default;

    virtual double value(const Eigen::VectorXd& x) const = 0;
    virtual Eigen::VectorXd gradient(const Eigen::VectorXd& x) const = 0;
    virtual Eigen::MatrixXd hessian(const Eigen::VectorXd& x) const = 0;
};

}