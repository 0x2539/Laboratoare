"""Tema3 CalculNumeric.

Metode iterative pentru sisteme de ecuatii liniare si
aproximarea valorilor
priprii ale unei matrice.
"""

import numpy as np
import sys
# from mpmath import mp
# from Jacobi import Jacobi
# from GaussSeidel import GaussSheidel
# from GC import GC
from metRot import metRot


def main(argv):
    """Main Function."""
    # mp.dps = 100
    # mp.prec = 100
    if (len(argv) == 2):
        n = int(argv[1])
    else:
        n = 10
    eps = 1e-10
    # A = np.ndarray((n, n), dtype=object)
    # b = np.ndarray((n,), dtype=object)
    #
    # for i in range(n):
    #     for j in range(n):
    #         A[i, j] = mp.mpf(0.0)
    #
    # for i in range(n):
    #     A[i, i] = mp.mpf(2.0 + 1.0 / (n**2))
    #     if i < n - 1:
    #         A[i, i+1] = mp.mpf(-1.0)
    #         A[i+1, i] = mp.mpf(-1.0)
    #       b[i] = mp.mpf(1.0/(n**2))
    A = np.zeros((n, n))
    b = np.full((n,), 1.0/(n**2))
    for i in range(n):
        A[i, i] = 2.0 + 1.0 / (n**2)
        if i < n - 1:
            A[i, i+1] = -1.0
            A[i+1, i] = -1.0

    # print (A)
    # x, no, sigmaO = Jacobi(A, b, 2, eps)
    # x, no, sigmaO = GaussSheidel(A, b, 10, eps)
    # print (x, no, sigmaO)
    # x = GC(A, b, eps)
    # pprint(x)
    x = metRot(A, eps)
    print(x)
    # print("A * x: ", A.dot(x))
    # print("b: ", b)


def pprint(arr, between='\n'):
    """Afisare cu mai multe zecimale."""
    print(between.join(map(lambda f: '%.20f' % f, arr)))


if __name__ == "__main__":
    main(sys.argv)
