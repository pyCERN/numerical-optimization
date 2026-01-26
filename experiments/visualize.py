import numpy as np
import matplotlib.pyplot as plt

history = np.loadtxt("experiments/history.csv")
x1_path, x2_path = history[:, 0], history[:, 1]

x1 = np.linspace(-4, 4, 100)
x2 = np.linspace(-4, 4, 100)
X1, X2 = np.meshgrid(x1, x2)
Z = X1**2 + X2**2

plt.contour(X1, X2, Z)
plt.plot(x1_path, x2_path)
plt.xlabel("x1")
plt.ylabel("x2")
plt.title("Steepest descent path")
plt.show()