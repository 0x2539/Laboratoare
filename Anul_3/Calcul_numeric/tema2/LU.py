"""Aflarea solutiilor prin factorizare LU."""
import numpy as np


def LU(A, b):
    """Aflarea solutiilor prin factorizare LU."""
    L = np.zeros(A.shape, dtype=object)
    U = np.zeros(A.shape, dtype=object)
    n = A.shape[0]
    y = np.zeros((n,), dtype=object)
    x = np.zeros((n,), dtype=object)

    # pasul de initializare
    L[:, 0] = A[:, 0]
    U[0, 0] = 1
    U[0, 1:] = A[0, 1:] / L[0, 0]
    # al doilea pas
    for k in range(1, n):
        for i in range(k, n):
            suma = 0
            for p in range(k):
                suma += L[i, p] * U[p, k]
            L[i, k] = A[i, k] - suma

        U[k, k] = 1

        for j in range(k+1, n):
            suma = 0
            for p in range(k):
                suma += L[k, p] * U[p, j]
            U[k, j] = (A[k, j] - suma) / L[k, k]

    # print (L)
    # print (U)
    # solutia y a sistemului Ly = b
    for i in range(n):
        suma = 0
        for k in range(i):
            suma += L[i, k] * y[k]

        y[i] = (b[i] - suma) / L[i, i]
    # solutia sistemului initial Ux = y

    for i in list(reversed(range(n))):
        suma = 0
        for k in range(i+1, n):
            suma += U[i, k] * x[k]
        x[i] = y[i] - suma
    return x
