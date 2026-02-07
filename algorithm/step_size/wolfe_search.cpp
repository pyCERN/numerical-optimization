#include "wolfe_search.h"
#include "../../test_functions/test_function_base.h"
#include <cmath>

namespace numerical_optimization::step_size {

WolfeSearch::WolfeSearch(
    const Eigen::VectorXd& x, const Eigen::VectorXd& p,
    const test_function::TestFunction& f,
    double c1, double c2,
    int maxIter, int maxIterZoom,
    double stepSizeMax,
    double sizeExpansionFactor
) : StepSizeStrategy(x, p, f),
    c1_(c1), c2_(c2),
    maxIter_(maxIter), maxIterZoom_(maxIterZoom),
    stepSizeMax_(stepSizeMax),
    sizeExpansionFactor_(sizeExpansionFactor)
{}

double WolfeSearch::phi(double stepSize) const {
    return f_.value(x_ + stepSize*p_);
}

double WolfeSearch::g_phi(double stepSize) const {
    return f_.gradient(x_ + stepSize*p_).dot(p_);
}

double WolfeSearch::findStepSize() const {
    // Here we assume that g_phi(0) is negative to make sure that the algorithm is toward decreasing direction.
    double phi0 = phi(0.0);
    double g_phi0 = g_phi(0.0);
    if (g_phi0 >= 0) {
        return 0.0;
    }

    double stepSize = std::min(1.0, stepSizeMax_);
    double stepSizePrev = 0.0;
    double solution = stepSize;
    
    for (int i = 0; i < maxIter_; i++) {
        double phiCur = phi(stepSize);
        double g_phiCur = g_phi(stepSize);
        if (phiCur > phi0 + c1_*stepSize*g_phi0 ||
            (i > 1 && phi(stepSize) >= phi(stepSizePrev))) {
            // Armijo condition violation.
            // Nailed down to the range where the solution is included.
            solution = zoom(stepSizePrev, stepSize);
            break;
        }
        if (std::abs(g_phiCur) <= -c2_*g_phi0) {
            // Curvature condition satisfied.
            // At this point, strong Wolfe condition is satisfied.
            solution = stepSize;
            break;
        }
        if (g_phiCur > 0.0) {
            // The sign of the gradient is changed and now the search is toward increasing direction.
            // So no need to go further in this direction.
            // Because of the first if condition, phi(stepSizePrev) > phi(stepSize)
            solution = zoom(stepSize, stepSizePrev);
            break;
        }

        // The gradient is still negative, so needs to go further and expand in this direction.
        stepSizePrev = stepSize;
        stepSize = std::min(stepSize * sizeExpansionFactor_, stepSizeMax_);
    }

    return solution;
}

double WolfeSearch::interpolate(double stepSizeLow, double stepSizeHigh) const {
    double g_phiLow = g_phi(stepSizeLow);
    double denom = 2 * (phi(stepSizeHigh) - phi(stepSizeLow) - g_phiLow * (stepSizeHigh - stepSizeLow));
    if (denom <= 0.0) {
        return (stepSizeLow + stepSizeHigh) / 2.0;
    }

    double num = g_phiLow * std::pow(stepSizeHigh - stepSizeLow, 2);
    double newStepSize = num / denom;
    if (newStepSize < stepSizeLow || newStepSize > stepSizeHigh) {
        return (stepSizeLow + stepSizeHigh) / 2.0;
    }

    return newStepSize;
}

double WolfeSearch::zoom(double stepSizeLow, double stepSizeHigh) const {
    double phi0 = phi(0.0);
    double g_phi0 = f_.gradient(x_).transpose() * p_;
    double solution {};
    for (int i = 0; i < maxIterZoom_; i++) {
        double stepSize = interpolate(stepSizeLow, stepSizeHigh);
        double phiCur = phi(stepSize);
        if (phiCur > phi0 + c1_*stepSize*g_phi0 || phi(stepSize) >= phi(stepSizeLow)) {
            // Armijo condition violation. Same as above Wolfe search.
            // No need to go further this step size, so stepSizeHigh is set to this value.
            stepSizeHigh = stepSize;
        }
        else {
            double g_phiCur = f_.gradient(x_ + stepSize*p_).transpose() * p_;
            if (std::abs(g_phiCur) <= -c2_*g_phi0) {
                // Curvature condition satisfied.
                solution = stepSize;
                break;
            }
            if (g_phiCur * (stepSizeHigh - stepSizeLow) >= 0.0) {
                stepSizeHigh = stepSizeLow;
            }

            // At this point, phi(stepSize) < phi(stepSizeLow).
            stepSizeLow = stepSize;
        }
    }

    return solution;
}

}