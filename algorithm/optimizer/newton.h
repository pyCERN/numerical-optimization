#ifndef NEWTON_H
#define NEWTON_H

#include "optimizer_base.h"

namespace numerical_optimization::optimizer {

class Newton : public LineSearchOptimizer {
public:
    Newton(double stepSize=1e-4, double tol=1e-6, int maxIter=10000);

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