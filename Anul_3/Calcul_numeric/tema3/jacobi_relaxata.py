import math
import matrix_utils

def get_norma_infinit(matrix):
	m = len(matrix)
	norma_infinit = 0

	for i in range(0, m):
		suma = sum([math.fabs(matrix[i][j]) for j in range(0, m)]) # TODO maybe not abs(a[i][j])
		# suma = sum([matrix[i][j] for j in range(0, m)]) # TODO maybe not abs(a[i][j])
		if norma_infinit < suma:
			norma_infinit = suma

	return norma_infinit

def calculation(matrix, q, temp_b, B, x_JR):
	m = len(matrix)

	y = [0 for i in range(0, m)]

	for i in range(0, m):
		suma = 0.0
		for j in range(0, m):
			suma += B[i][j] * x_JR[j]
		y[i] = suma + temp_b[i]

	norma_suma = 0.0;
	for i in range(0, m):
		suma = 0.0;
		for j in range(0, m):
		    suma += matrix[i][j] * (y[i] - x_JR[i]) * (y[j] - x_JR[j])
		norma_suma += suma

	er = math.sqrt(norma_suma)
	# er = norma_suma
	for i in range(0, m):
		x_JR[i] = y[i]

	q += 1

	return er, q, x_JR

def main_loop(matrix, iteratii, norma_infinit, b_array):
	m = len(matrix)
	mo = 0
	suma = 0.0
	sigma = 0.0
	sigmao = 0.0
	p = 10
	err = 0.0
	t = norma_infinit
	x_JR = [0 for i in range(0, m)]
	epsilon = 10.0**(-10.0)

	for k in range(0, p-1):
		sigma = ((2.0 * k) / (p*t))
		print 'sigma', sigma * p

		B = matrix_utils.get_matrix(m, m)
		temp_b = [0 for i in range(0, m)]

		for i in range(0, m):
			for j in range(0, m):
				if i == j:
					B[i][j] = 1.0 - sigma * matrix[i][j]
				else:
					B[i][j] = -(sigma * matrix[i][j])
			temp_b[i] = sigma * b_array[i]

		temp_x = [0 for i in range(0, m)]

		q = 0
		err, q, temp_x = calculation(matrix, q, temp_b, B, temp_x)
		while err >= epsilon:
			err, q, temp_x = calculation(matrix, q, temp_b, B, temp_x)

		# if k == 0:
		# 	mo = q
		# 	sigmao = sigma
		for i in range(0, m):
			x_JR[i] = temp_x[i]
		# elif q < mo:
		# 	mo = q
		# 	sigmao = sigma
		# 	for i in range(0, m):
		# 		x_JR[i] = temp_x[i]

	print 'solution', sorted(x_JR)




