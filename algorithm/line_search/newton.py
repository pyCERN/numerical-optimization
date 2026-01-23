import numpy as np

def newton(f, grad_f, hess_f, x0, alpha=1e-4, tol=1e-6, max_iter=10000):
    x = x0.copy()
    history = [x.copy()]

    for k in range(max_iter):
        g = grad_f(x)
        if np.linalg.norm(g) < tol:
            break
        hess = hess_f(x)
        x -= alpha * np.linalg.solve(hess, g)
        history.append(x.copy())

    return x, np.array(history)