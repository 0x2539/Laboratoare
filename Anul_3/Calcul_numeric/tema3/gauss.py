import math
import matrix_utils


sigma = 0.0
sigmao = 0.0
xo = []
y = []
x = []
xi = None
p = 0
m = 0
mo = 0
suma = 0.0
suma2 = 0.0
temp = 0.0
er = 0.0

def calculations(A, n, b):
    global sigma
    global sigmao
    global x
    global xo
    global y
    global xi
    global p
    global m
    global mo
    global suma
    global suma2
    global temp
    global er

    y[0] = (1.0 - sigma) * x[0]
    suma = 0
    for j in range(1, n):
        suma = suma + A[0][j] * x[j]

    temp = sigma / A[0][0]
    y[0] = y[0] + temp * (b[0] - suma)
    for i in range(1, n):
        y[i] = (1 - sigma) * x[i]
        suma = 0
        for j in range(0, i):
            suma = suma + A[i][j] * y[j]

        suma2 = 0
        for j in range(i+1, n):
            suma2 = suma2 + A[i][j] * x[j]

        temp = (sigma / A[i][i])
        y[i] = y[i] + temp * (b[i] - suma - suma2)

    suma = 0
    for i in range(0, n):
        for j in range(0, n):
            suma = suma + A[i][j] * (y[i] - x[i]) * (y[j] - x[j])

    er = (math.sqrt(suma))
    for i in range(0, n):
        x[i] = y[i]

    m += 1
    return m

def GS(A, iteratii, n, b):

    global sigma
    global sigmao
    global x
    global xo
    global y
    global xi
    global p
    global m
    global mo
    global suma
    global suma2
    global temp
    global er

    x = [0 for i in range(0, n)]
    xo = [0 for i in range(0, n)]
    y = [0 for i in range(0, n)]
    xi = matrix_utils.get_matrix(n*n, n)
    p = iteratii

    for i in range(0, n):
        x[i] = 0
        xo[i] = 0
        y[i] = 0
        xi[0][i] = 0
    
    for k in range(0, p):
        sigma = 2.0 * k
        sigma = sigma / p
        m = 0

        epsilon = 10.0**(-10.0)
        m = calculations(A, n, b)
        while er >= epsilon:
            m = calculations(A, n, b)

        # if k == 0:
        #     mo = m
        #     sigmao = sigma
        for i in range(0, n):
            xo[i] = x[i]

        # elif m < mo:
        #     mo = m
        #     sigmao = sigma
        #     for i in range(0, n):
        #         xo[i] = x[i]

    print xo

