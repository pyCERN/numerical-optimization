#include "optimizer_base.h"

namespace optimizer {

class SteepestDescent : public LineSearchOptimizer {
public:
    SteepestDescent(double alpha=1e-4, double tol=1e-6, int maxIter=10000);

    void optimize(
        const Eigen::VectorXd& x0,
        const test_function::TestFunction& f
    );

private:
    double alpha_;
    double tol_;
    int maxIter_;
};

}