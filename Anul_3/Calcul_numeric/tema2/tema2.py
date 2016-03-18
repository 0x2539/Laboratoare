from utilFunc import combination
import sys
import numpy as np
from LU import LU
from Cholesky import Cholesky
from QR import QR
from mpmath import mp


def main(argv):
    mp.dps = 1000
    mp.prec = 1000

    if (len(argv) == 3):
        n = int(argv[1])
        p = int(argv[2])
    else:
        n = 5
        p = 10

    A = np.zeros((n, n), dtype=object)
    b = np.ones((n,), dtype=object)
    # A = [[0, 4, 5], [-1, -2, -3], [0, 0, 1]]
    # A = np.array(A)
    # b = [23, -14, 3]
    # b = np.array(b)

    for i in range(n):
        for j in range(n):
            A[i, j] = mp.mpf(combination(p+j, i))

    # print (A)
    # print (A.T.dot(b))

    x = Cholesky(A.T.dot(A), A.T.dot(b))
    y = np.dot(A.T.dot(A), x)
    print (x)
    # print (A.T.dot(b))
    # print (y)
    # x = QR(A, b)
    # y = np.dot(A, x)
    # print (A)
    # print (b)
    # print (y)

if __name__ == "__main__":
    main(sys.argv)
