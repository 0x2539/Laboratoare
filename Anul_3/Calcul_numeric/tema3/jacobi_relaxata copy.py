import math
import matrix_utils
from decimal import *

getcontext().prec = 30

def get_norma_infinit(matrix):
	m = len(matrix)
	norma_infinit = Decimal(0)

	for i in range(0, m):
		suma = Decimal(sum([abs(matrix[i][j]) for j in range(0, m)])) # TODO maybe not abs(a[i][j])
		# suma = sum([matrix[i][j] for j in range(0, m)]) # TODO maybe not abs(a[i][j])
		if norma_infinit < suma:
			norma_infinit = suma

	return norma_infinit

def calculation(matrix, it, temp_b, B, x_JR):
	m = len(matrix)

	y = [Decimal(0) for i in range(0, m)]

	for i in range(0, m):
		suma = Decimal(0.0)
		for j in range(0, m):
			suma += B[i][j] * x_JR[j]
		y[i] = suma + temp_b[i]

	norma_suma = Decimal(0.0);
	for i in range(0, m):
		suma = Decimal(0.0)
		for j in range(0, m):
		    suma += matrix[i][j] * (y[i] - x_JR[i]) * (y[j] - x_JR[j])
		norma_suma += suma

	er = norma_suma.sqrt()
	# er = norma_suma
	for i in range(0, m):
		x_JR[i] = y[i]

	it += 1

	return er, it, x_JR

def main_loop(matrix, iteratii, norma_infinit, b_array):
	m = len(matrix)
	mo = Decimal(0)
	suma = Decimal(0.0)
	sigma = Decimal(0.0)
	sigmao = Decimal(0.0)
	p = Decimal(10)
	err = Decimal(0.0)
	t = norma_infinit
	x_JR = [0 for i in range(0, m)]
	epsilon = Decimal(10.0)**Decimal(-10.0)

	l = Decimal(2) / norma_infinit

	for k in range(1, p + 1):
		sigma = (l / p) * Decimal(k)
		# sigma = ((2.0 * k) / (p*t))
		print 'k: %s, sigma %s' % (k, sigma)

		B = matrix_utils.get_matrix(m, m, Decimal(0))
		temp_b = [Decimal(0) for i in range(0, m)]

		for i in range(0, m):
			for j in range(0, m):
				if i == j:
					B[i][j] = Decimal(1.0) - sigma * matrix[i][j]
				else:
					B[i][j] = -(sigma * matrix[i][j])
			temp_b[i] = sigma * b_array[i]

		temp_x = [Decimal(0) for i in range(0, m)]

		it = 0
		err, it, temp_x = calculation(matrix, it, temp_b, B, temp_x)
		while err > epsilon:
			if it % 1000 == 0:
				print it, err, epsilon
			err, it, temp_x = calculation(matrix, it, temp_b, B, temp_x)

		if k == 1:
			mo = it
			sigmao = sigma
			for i in range(0, m):
				x_JR[i] = temp_x[i]
		elif it < mo:
			mo = it
			sigmao = sigma
			for i in range(0, m):
				x_JR[i] = temp_x[i]

	print 'mo', mo
	print 'sigmao', sigmao
	print 'solution', sorted(x_JR)




