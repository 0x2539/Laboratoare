import matrix_utils
import jacobi_relaxata
import gradient
import gauss

def create_input(size):

	matrix = matrix_utils.get_matrix(size, size)

	for i in range(0, size):
		matrix[i][i] = 2.0 + (1.0 / (size ** 2.0))

	for i in range(0, size - 1):
		matrix[i][i+1] = -1
		matrix[i+1][i] = -1
	
	b_array = [1.0 / (size ** 2.0) for i in range(0, size)]

	return matrix, b_array

def solve(size):
	matrix, b_array = create_input(size)
	# norma_infinit = jacobi_relaxata.get_norma_infinit(matrix)
	# jacobi_relaxata.main_loop(matrix, size, norma_infinit, b_array)
	# gradient.GC(matrix, len(matrix), b_array)
	gauss.GS(matrix, len(matrix), len(matrix), b_array)


if __name__ == '__main__':
	solve(10)