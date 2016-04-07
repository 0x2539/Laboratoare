"""Metoda rotatiilor."""
from math import sqrt
from math import pi
from math import atan2
from math import sin
from math import cos
import numpy as np


def modul(x):
    """Modulul lui x."""
    m = x.shape[0]
    mod = sqrt(sum(x[i, j]**2 for i in range(m) for j in range(m) if i != j))
    return mod


def maxx(x):
    """Maximul medulul elementelor de sub diagonala principala."""
    m = x.shape[0]
    maxim = 0
    p = 0
    q = 0
    for i in range(m):
        for j in range(m):
            if i < j:
                if abs(x[i, j]) > maxim:
                    maxim = abs(x[i, j])
                    p = i
                    q = j
    return p, q


def metRot(A, eps):
    """Metoda rotatiilor."""
    x = A
    m = A.shape[0]
    while modul(x) >= eps:
        p, q = maxx(x)
        if x[p, p] == x[q, q]:
            theta = pi / 4
        else:
            theta = 1 / 2 * atan2(2 * x[p, q], x[p, p] - x[q, q])
        c = cos(theta)
        s = sin(theta)
        y = np.empty_like(x)
        for i in range(m):
            for j in range(m):
                if i not in (p, q) and j not in (p, q):
                    y[i, j] = x[i, j]
                if j not in (p, q):
                    y[p, j] = c * x[p, j] + s * x[q, j]
                    y[j, p] = y[p, j]
                    y[q, j] = - s * x[p, j] + c * x[q, j]
                    y[j, q] = y[q, j]
        y[p, q] = 0
        y[q, p] = 0
        y[p, p] = c ** 2 * x[p, p] + 2 * c * s * x[p, q] + s ** 2 * x[q, q]
        y[q, q] = s ** 2 * x[p, p] - 2 * c * s * x[p, q] + c ** 2 * x[q, q]
        x = y
        # print(modul(x))
    return list(reversed(x.diagonal()))
