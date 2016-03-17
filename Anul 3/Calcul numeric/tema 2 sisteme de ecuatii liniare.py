# LU
import matrix_utils

def get_L_matrix_initial(matrix):
	"""
	proposition 9
	"""
	l_matrix = matrix_utils.get_matrix(len(matrix))

	for i in range(len(matrix)):
		l_matrix[i][0] = matrix[i][0]

	return l_matrix

def get_U_matrix_initial(matrix):
	"""
	proposition 9
	"""
	u_matrix = matrix_utils.get_matrix(len(matrix))

	u_matrix[0][0] = 1

	for i in range(1, len(matrix)):
		u_matrix[0][i] = matrix[0][i] / l_matrix[0][0]

	return u_matrix

def get_LU_matrices_at_pase(matrix, l_matrix, u_matrix, pase):
	k = pase

	u_matrix[k][k] = 1

	for i in range(k, len(matrix)):
	
		l_matrix[i][k] = matrix[i][k] - sum([l_matrix[i][p] * u_matrix[p][k] for p in range(k)])

		# A
		# j = i + 1
		# if j < len(matrix):
		# 	u_matrix[k][j] = (a[k][j] - sum([l_matrix[k][p] * u_matrix[p][j] for p in range(k)])) / l_matrix[k][k]

	# B
	for j in range(k + 1, len(matrix)):
	
		u_matrix[k][j] = (a[k][j] - sum([l_matrix[k][p] * u_matrix[p][j] for p in range(k)])) / l_matrix[k][k]

	# TODO choose A or B^

	return l_matrix, u_matrix

def get_LU_matrices(matrix):
	l_matrix = get_L_matrix_initial(matrix)
	u_matrix = get_U_matrix_initial(matrix)

	# prop 10
	for k in range(1, len(matrix)):
		l_matrix, u_matrix = get_LU_matrices_at_pase(matrix, l_matrix, u_matrix, k)

	return l_matrix, u_matrix

matrix = [
	[1, 2, 3],
	[4, 5, 6],
	[7, 8, 10]
]
# get_L(matrix)
matrix_utils.check_determinanti_de_colt(matrix)
