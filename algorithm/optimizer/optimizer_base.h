#ifndef OPTIMIZER_BASE_H
#define OPTIMIZER_BASE_H

#include <Eigen/Dense>
#include <vector>

namespace numerical_optimization::test_function {
    class TestFunction;
}

namespace numerical_optimization::optimizer {

class OptimizationResult {
public:
    OptimizationResult()
        : result_{}, history_{}
    {}

    Eigen::VectorXd result() const { return result_; }
    std::vector<Eigen::VectorXd> history() const { return history_; }
    void setSolution(const Eigen::VectorXd& x) { result_ = x; }
    void addHistory(const Eigen::VectorXd& x) { history_.push_back(x); }

private:
    Eigen::VectorXd result_;
    std::vector<Eigen::VectorXd> history_;
};

class LineSearchOptimizer {
public:
    virtual ~LineSearchOptimizer() = default;

    virtual void optimize(
        const Eigen::VectorXd& x0,
        const test_function::TestFunction& f
    ) = 0;

    OptimizationResult result() const { return result_; }

protected:
    OptimizationResult result_;
};

}

#endif