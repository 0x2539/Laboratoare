"""Metoda QR."""
import numpy as np


def QR(A, b):
    """Metoda QR."""
    Q = np.zeros(A.shape, dtype=object)
    R = np.zeros(A.shape, dtype=object)
    n = A.shape[0]
    y = np.zeros((n,), dtype=object)
    x = np.zeros((n,), dtype=object)

    # Pentru k = 0
    R[0, 0] = np.sqrt(np.sum(np.square(A[:, 0])))
    Q[:, 0] = A[:, 0] / R[0, 0]
    # print (Q)
    # Pentru k >= 1
    for k in range(1, n):
        for j in range(k):
            R[j, k] = np.dot(A[:, k], Q[:, j])
        R[k, k] = np.sqrt(np.sum(np.square(A[:, k])) - np.sum(np.square(R[:k, k])))
        for i in range(n):
            Q[i, k] = (A[i, k] - np.dot(R[:k, k], Q[i, :k])) / R[k, k]
    # Rezolvam intai sistemul y = Q.T * b
    y = np.dot(Q.T, b)
    # print (y)
    # Apoi rezolvam sistemul triungiular R*x = y
    for i in list(reversed(range(n))):
        if (np.dot(R[i, i+1:], x[i+1:])):
            x[i] = (y[i] - np.dot(R[i, i+1:], x[i+1:])) / R[i, i]
        else:
            x[i] = y[i] / R[i, i]
    return x
