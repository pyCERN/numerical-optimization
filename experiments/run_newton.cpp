#include "../algorithm/optimizer/newton.h"
#include "../algorithm/step_size/backtrack_search.h"
#include "../algorithm/step_size/fixed_step_size.h"
#include "../algorithm/step_size/wolfe_search.h"
#include "../test_functions/rosenbrock.h"
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <memory>

using namespace numerical_optimization;

int main(int argc, char* argv[]) {
    test_function::Rosenbrock f(1.0, 100.0);

    std::unique_ptr<step_size::StepSizeStrategy> strategy;
    if (argc > 1) {
        if (std::string(argv[1]) == "fixed") {
            strategy = std::make_unique<step_size::FixedStepSize>(1.0);
        }
        else if (std::string(argv[1]) == "backtrack") {
            strategy = std::make_unique<step_size::BacktrackSearch>(1e-4, 0.8, 10000);
        }
        else if (std::string(argv[1]) == "wolfe") {
            strategy = std::make_unique<step_size::WolfeSearch>(1e-4, 0.9, 10000, 10000, 10.0, 2.0);
        }
    }

    optimizer::Newton opt(std::move(strategy), 1.0, 1e-6, 100000);

    Eigen::VectorXd x0(2);
    x0 << -1.2, 1.0;

    opt.optimize(x0, f);

    std::ofstream fs("experiments/history.csv");
    std::vector<Eigen::VectorXd> history = opt.result().history();
    for (size_t iter = 0; iter < history.size(); iter++) {
        fs << history[iter][0] << " " << history[iter][1] << "\n";
    }
    fs.close();

    int ret = std::system("python experiments/visualize.py");
    if (ret != 0) {
        std::cerr << "Python script run failed\n";
        return 1;
    }

    return 0;
}