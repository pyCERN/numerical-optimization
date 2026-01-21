import numpy as np

from numerical_optimization.algorithm.line_search.steepest_descent import gradient_descent
from numerical_optimization.test_functions.test_functions import rosenbrock, grad_rosenbrock

x0 = np.array([-1.2, 1.0])
x_star, hist = gradient_descent(rosenbrock, grad_rosenbrock, x0)
print(x_star)
print(hist)