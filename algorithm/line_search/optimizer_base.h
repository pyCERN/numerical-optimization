#include <Eigen/Dense>
#include <vector>

namespace test_function {
    class TestFunction;
}

namespace optimizer {

class LineSearchOptimizer {
public:
    virtual ~LineSearchOptimizer() = default;

    virtual void optimize(
        const Eigen::VectorXd& x0,
        const test_function::TestFunction& f
    ) = 0;

    virtual std::vector<Eigen::VectorXd> history() const { return history_; };

protected:
    Eigen::VectorXd result_;
    std::vector<Eigen::VectorXd> history_;
};

}