import numpy as np

def rosenbrock(x: np.ndarray, a=1, b=100):
    return (a - x[0]) ** 2 + b * (x[1] - x[0]**2) ** 2

def grad_rosenbrock(x: np.ndarray, a=1, b=100):
    return np.array([
        -2 * (a - x[0]) - 4*b*x[0] * (x[1] - x[0]**2),
        2*b * (x[1] - x[0]**2)
    ])

def hessian_rosenbrock(x: np.ndarray, a=1, b=100):
    h11 = 2 - 4*b*x[1] + 12*b*x[0]**2
    h12 = -4*b*x[0]
    h21 = -4*b*x[0]
    h22 = 2*b
    return np.array([
        [h11, h12],
        [h21, h22]
    ])