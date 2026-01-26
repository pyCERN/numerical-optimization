#include "../algorithm/line_search/newton.h"
#include "../test_functions/rosenbrock.h"
#include <cstdlib>
#include <iostream>
#include <fstream>

int main(void) {
    test_function::Rosenbrock f { 1.0, 100.0 };
    optimizer::Newton opt { 1e-3, 1e-6, 10000 };

    Eigen::VectorXd x0(2);
    x0 << -1.2, 1.0;

    opt.optimize(x0, f);

    std::ofstream fs { "experiments/history.csv" };
    std::vector<Eigen::VectorXd> history { opt.history() };
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