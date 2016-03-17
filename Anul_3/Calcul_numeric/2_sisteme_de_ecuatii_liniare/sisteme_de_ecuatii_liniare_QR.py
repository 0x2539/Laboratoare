import matrix_utils
import math

def check_if_QR_should_fail(r_matrix):
	m = len(r_matrix)
	for i in range(m):
		if r_matrix[i][i] == 0:
			return True
	return False

def initial_init(matrix):
	m = len(matrix)
	
	r = matrix_utils.get_matrix(m)
	q = matrix_utils.get_matrix(m)
	
	r[0][0] = math.sqrt(sum([matrix[i][0] ** 2 for i in range(m)]))

	for i in range(m):
		q[i][0] = matrix[i][0] / r[0][0]

	return r, q

def prop_14(matrix, r_matrix, q_matrix):
	m = len(matrix)

	for k in range(1, m):
		for j in range(k):

			r_matrix[j][k] = sum([matrix[i][k] * q_matrix[i][j] for i in range(m)])

		r_matrix[k][k] = math.sqrt(
			sum([matrix[i][k] ** 2 for i in range(m)]) - sum([r_matrix[i][k] ** 2 for i in range(k)])
		)

		for i in range(m):
			q_matrix[i][k] = (1.0 / r_matrix[k][k]) * (matrix[i][k] - sum(r_matrix[j][k] * q_matrix[i][j] for j in range(k)))

	if check_if_QR_should_fail(r_matrix):
		print 'FAILED, r_matrix has a 0 value:', r_matrix
		return [[]], [[]]

	return r_matrix, q_matrix

def find_y_solution(matrix, q_matrix, b_array):
	m = len(matrix)

	y = [0 for i in range(m)]

	for i in range(m):
		y[i] = sum([q_matrix[i][j] * b_array[j] for j in range(m)])

	return y

def find_x_solution(matrix, r_matrix, y_array):
	m = len(matrix)
	# Proposition 15

	if check_if_QR_should_fail(r_matrix):
		print 'FAILED, r_matrix has a 0 value:', r_matrix
		return []

	x = [0 for i in range(m)]

	x[m - 1] = y_array[m-1] / r_matrix[m-1][m-1]

	for i in range(m - 2, -1, -1):
		x[i] = (1.0 / r_matrix[i][i]) * (y_array[i] - sum([r_matrix[i][j] * x[j] for j in range(i+1, m)]))

	return x










