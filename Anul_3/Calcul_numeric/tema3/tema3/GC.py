"""Metoda Gradientului Conjugat."""
import numpy as np


def GC(A, b, eps):
    """Metoda Gradientului Conjugat."""
    m = A.shape[0]
    x = np.zeros((m, ))

    r0 = b - A.dot(x)
    v0 = r0
    while True:
        norm_prev_r0 = r0.dot(r0)
        alpha = norm_prev_r0 / A.dot(v0).dot(v0)
        x0 = x
        x = x + alpha * v0
        r0 = b - A.dot(x)
        c = r0.dot(r0) / norm_prev_r0
        prev_v0 = v0
        v0 = r0 + c * prev_v0
        xx = x - x0
        if (xx).dot(xx) <= eps:
            break
    return x
