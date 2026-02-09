#ifndef NEWTON_H
#define NEWTON_H

#include "optimizer_base.h"

namespace numerical_optimization::optimizer {

class Newton : public LineSearchOptimizer {
public:
    Newton(
        std::unique_ptr<step_size::StepSizeStrategy> strategy,
        double stepSize, double tol, int maxIter
    );

    void optimize(
        const Eigen::VectorXd& x0,
        const test_function::TestFunction& f
    );

private:
    double stepSize_;
    double tol_;
    int maxIter_;
};

}

#endif