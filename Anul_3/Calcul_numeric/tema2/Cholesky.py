import numpy as np


def Cholesky(A, b):
    L = np.zeros(A.shape, dtype=object)
    n = A.shape[0]
    y = np.zeros((n,), dtype=object)
    x = np.zeros((n,), dtype=object)
    # Construiesc L
    for j in range(n):
        L[j, j] = np.sqrt(A[j, j] - np.sum([a**2 for a in L[j, :j]]))
        for i in range(j+1, n):
            if np.dot(L[i, :j], L[j, :j]):
                L[i, j] = (A[i, j] - np.dot(L[i, :j], L[j, :j])) / L[j, j]
            else:
                L[i, j] = A[i, j] / L[j, j]
    # L * L.T * x = y
    # Solutia y a sistemului L * y = b
    # print (L)
    for i in range(n):
        if np.dot(L[i, :i], y[:i]):
            y[i] = (b[i] - np.dot(L[i, :i], y[:i])) / L[i, i]
        else:
            y[i] = b[i] / L[i, i]
    # print (y)
    # Solutia, x, sistemului initial L.T * x = y
    for i in list(reversed(range(n))):
        if np.dot(L[i+1:, i], x[i+1:]):
            x[i] = (y[i] - np.dot(L[i+1:, i], x[i+1:])) / L[i, i]
        else:
            x[i] = y[i] / L[i, i]
    return x
