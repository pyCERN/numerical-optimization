import numpy as np

def gradient_descent(f, grad_f, x0, alpha=1e-4, tol=1e-6, max_iter=10000):
    x = x0.copy()
    history = [x.copy()]

    for k in range(max_iter):
        g = grad_f(x)
        if np.linalg.norm(g) < tol:
            break
        x -= alpha * g
        history.append(x.copy())

    return x, np.array(history)
