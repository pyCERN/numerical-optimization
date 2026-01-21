import numpy as np

def rosenbrock(x: np.ndarray, a=1, b=100):
    return (a - x[0]) ** 2 + b * (x[1] - x[0]**2) ** 2

def grad_rosenbrock(x: np.ndarray, a=1, b=100):
    return np.array([
        -2 * (a - x[0]) - 4*b * (x[1] - x[0]**2),
        2*b * (x[1] - x[0]**2)
    ])