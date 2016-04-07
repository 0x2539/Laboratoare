"""Metoda GaussSheidel relaxata."""
import numpy as np
from math import sqrt
# from mpmath import mp


def GaussSheidel(A, a, p, eps):
    """Metoda GaussSheidel relaxata."""
    m = A.shape[0]
    for k in range(1, p):

        sigma = 2 / p * k
        x = np.zeros((m,))
        # x = np.ndarray((m,), dtype=object)
        # for i in range(m):
        #     x[i] = mp.mpf(0.0)

        n = 0
        na = float('inf')
        while (na > eps):
            n += 1
            y = np.ndarray((m,), dtype=float)
            for i in range(m):
                sum1 = 0
                for j in range(i):
                    sum1 += A[i, j] * y[j]
                sum2 = 0
                for j in range(i+1, m):
                    sum2 += A[i, j] * x[j]
                y[i] = (1 - sigma) * x[i] + sigma / A[i, i] * (a[i] - sum1 - sum2)

            na = sqrt(sum(A[i, j] * (y[i] - x[i]) * (y[j] - x[j])
                        for i in range(m) for j in range(m)))
            x = y
            print(na, na > eps)
        if k == 1:
            no = n
            sigmaO = sigma
        elif k > 1:
            if n < no:
                no = n
                sigmaO = sigma
        z = x
    return z, no, sigmaO
