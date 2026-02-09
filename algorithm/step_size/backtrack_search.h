#ifndef BACKTRACK_SEARCH_H
#define BACKTRACK_SEARCH_H

#include "step_size_base.h"

namespace numerical_optimization::step_size {

class BacktrackSearch : public StepSizeStrategy {
public:
    BacktrackSearch(
        double c,
        double rho,
        int maxIter
    );

    double findStepSize(
        const Eigen::VectorXd& x, const Eigen::VectorXd& p,
        const test_function::TestFunction& f
    ) const;

private:
    double c_;   // For Armijo condition
    double rho_; // shrinkage factor
    int maxIter_;
};

}

#endif