import matrix_utils
import math

def check_matrix_transpose(matrix):
	return matrix == matrix_utils.get_matrix_transpose(matrix)

def get_L_matrix(matrix):
	m = len(matrix)

	l_matrix = matrix_utils.get_matrix(m)

	for j in range(m):
		
		l_matrix[j][j] = math.sqrt(matrix[j][j] - sum([l_matrix[j][k] ** 2 for k in range(j)]))

		for i in range(j + 1, m):
			l_matrix[i][j] = (matrix[i][j] - sum([l_matrix[i][k] * l_matrix[j][k] for k in range(j)])) / l_matrix[j][j]

	return l_matrix

def find_y_solution(l_matrix, b_matrix):
	m = len(matrix)
	# Proposition 12 (suma incepe de la 1 pana la i-1, si i incepe de la 1, deci suma la inceput o sa fie de la 1 la 0???)
	y = [0 for x in range(m)]

	for i in range(m):
		y[i] = (b_matrix[i] - sum([l_matrix[i][k] * y[k] for k in range(i)])) / l_matrix[i][i]

	return y

def find_x_solution(l_matrix, y_array, b_matrix):
	m = len(matrix)
	# Proposition 13 (suma incepe de la 1 pana la i-1, si i incepe de la 1, deci suma la inceput o sa fie de la 1 la 0???)
	x = [0 for x in range(m)]

	for i in range(m - 1, -1, -1):
		x[i] = (y_array[i] - sum([l_matrix[k][i] * x[k] for k in range(i+1, m)])) / l_matrix[i][i]

	return x

matrix = [
	[1, 2, 3],
	[4, 5, 6],
	[7, 8, 10]
]
matrix = [
	[1, 2, 3],
	[2, 4, 5],
	[3, 5, 6]
]
print matrix_utils.get_matrix_transpose(matrix)