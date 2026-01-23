import numpy as np
import matplotlib.pyplot as plt

from numerical_optimization.algorithm.line_search.steepest_descent import steepest_descent
from numerical_optimization.test_functions.test_functions import rosenbrock, grad_rosenbrock

x0 = np.array([-1.2, 1.0])
x_star, hist = steepest_descent(
    rosenbrock, grad_rosenbrock, x0, alpha=1e-3, tol=1e-6, max_iter=10000
)

x1 = np.linspace(-4, 4, 100)
x2 = np.linspace(-4, 4, 100)
X1, X2 = np.meshgrid(x1, x2)
Z = X1**2 + X2**2

print(x_star)

plt.contour(X1, X2, Z)
plt.plot(hist[:, 0], hist[:, 1])
plt.xlabel("x1")
plt.ylabel("x2")
plt.title("Steepest descent path")
plt.show()