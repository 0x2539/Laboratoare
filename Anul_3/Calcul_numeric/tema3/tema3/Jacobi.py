"""Metoda Jacobi relaxata."""
import numpy as np
import mpmath as mp
# from math import sqrt


def Jacobi(A, a, p, eps):
    """Metoda Jacobi relaxata."""
    m = A.shape[0]
    ni = np.max(np.sum(np.array(list(map(abs, A))), axis=0))
    l = 2 / ni
    for k in range(1, p):
        sigma = l / p * k
        x = np.zeros((m,))
        # x = np.ndarray((m,), dtype=object)
        # for i in range(m):
        #     x[i] = mp.mpf(0.)
        b = sigma * a
        I = np.eye(m)
        # I = np.ndarray((m, m), dtype=object)
        # for i in range(m):
        #     for j in range(m):
        #         if i == j:
        #             I[i, i] = mp.mpf(1.)
        #         else:
        #             I[i, j] = mp.mpf(0.)

        # import pdb; pdb.set_trace()
        Bsigma = I - sigma * A

        # step 2
        n = 0
        na = float('inf')
        while na > eps:
            n += 1
            x0 = x
            y = Bsigma.dot(x) + b
            x = y
            # na = sqrt(sum(A[i, j] * (y[i] - x0[i]) * (y[j] - x0[j])
            #             for i in range(m) for j in range(m)))

            q = np.max(np.sum(np.array(list(map(abs, Bsigma))), axis=1))
            na = q / (1 - q) * np.max(np.sum(np.array(list(map(abs, x - x0)))), axis=0)
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
