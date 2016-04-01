import math
import matrix_utils


alfa = []
ci = []
xi = None
ri = None
vi = None
suma = 0.0
suma2 = 0.0
suma3 = 0.0
er = 0.0
def init(n):
    global alfa
    global ci
    global xi
    global ri
    global vi
    alfa = [0 for i in range(0, n)]
    ci = [0 for i in range(0, n*n)]
    xi = matrix_utils.get_matrix(n*n, n)
    ri = matrix_utils.get_matrix(n*n, n)
    vi = matrix_utils.get_matrix(n*n, n)


def calculations(A, n, k, b):
    global alfa
    global ci
    global xi
    global ri
    global vi
    global suma
    global suma2
    global suma3
    global er

    suma = 0
    for j in range(0, n):
        suma += ri[k][j] * ri[k][j]

    suma2 = 0
    for i in range(0, n):
        suma3 = 0
        for j in range(0, n):
            suma3 = suma3 + A[i][j] * vi[k][j]

        suma2 += suma3 * vi[k][i]

    alfa[k] = (suma / suma2)
    for i in range(0, n):
        xi[k + 1][i] = xi[k][i] + alfa[k] * vi[k][i]

    suma = 0
    for i in range(0, n):
        suma += (xi[k + 1][j] - xi[k][j]) * (xi[k + 1][j] - xi[k][j])

    er = (math.sqrt(suma));
    for i in range(0, n):
        suma = 0
        for j in range(0, n):
            suma += A[i][j] * xi[k + 1][j]

        ri[k + 1][i] = b[i] - suma

    suma = 0
    suma2 = 0
    for j in range(0, n):
        suma += ri[k + 1][j] * ri[k + 1][j]
        suma2 += ri[k][j] * ri[k][j]

    ci[k] = suma / suma2
    for i in range(0, n):
        vi[k + 1][i] = ri[k + 1][i] + ci[k] * vi[k][i]
    k += 1

    return k

def GC(A, n, b):
    global alfa
    global ci
    global xi
    global ri
    global vi
    global suma
    global suma2
    global suma3
    global er

    init(n)

    for i in range(0, n):
        suma = 0
        for j in range(0, n):
            suma = suma + A[i][j] * xi[0][i]
        ri[0][i] = b[i] - suma
        vi[0][i] = ri[0][i]
        xi[0][i] = 0

    k = 0

    k = calculations(A, n, k, b)
    epsilon = 10.0**(-10.0)
    while er >= epsilon:
        k = calculations(A, n, k, b)

    print xi[k-1]

