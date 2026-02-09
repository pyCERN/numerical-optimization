#ifndef WOLFE_SEARCH_H
#define WOLFE_SEARCH_H

#include "step_size_base.h"

namespace numerical_optimization::step_size {

class WolfeSearch : public StepSizeStrategy {
public:
    WolfeSearch(
        double c1, double c2,
        int maxIter, int maxIterZoom,
        double stepSizeMax,
        double sizeExpansionFactor
    );

    double findStepSize(
        const Eigen::VectorXd& x, const Eigen::VectorXd& p,
        const test_function::TestFunction& f
    ) const;

private:
    double phi(
        double stepSize,
        const Eigen::VectorXd& x, const Eigen::VectorXd& p,
        const test_function::TestFunction& f
    ) const;
    double g_phi(
        double stepSize,
        const Eigen::VectorXd& x, const Eigen::VectorXd& p,
        const test_function::TestFunction& f
    ) const;
    double interpolate(
        double stepSizeLow, double stepSizeHigh,
        const Eigen::VectorXd& x, const Eigen::VectorXd& p,
        const test_function::TestFunction& f
    ) const;
    double zoom(
        double stepSizeLow, double stepSizeHigh,
        const Eigen::VectorXd& x, const Eigen::VectorXd& p,
        const test_function::TestFunction& f
    ) const;

    double c1_; // For Armijo condition
    double c2_; // For curvature / strong Wolfe condition
    int maxIter_;
    int maxIterZoom_;
    double stepSizeMax_;
    double sizeExpansionFactor_;
};

}

#endif