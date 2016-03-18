"""Functii utile."""
from math import factorial


def combination(n, k):
    """Combinari de n luate cate k."""
    if k > n:
        raise ValueError("k<=n")
    elif k > n // 2:
        k = n - k

    if k == 1:
        return n
    elif k == 0:
        return 1
    else:
        return factorial(n) / (factorial(k) * factorial(n - k))
