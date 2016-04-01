from decimal import *
import matrix_utils
import jacobi_relaxata_copy
import gradient
import gauss

def create_input(size):

	matrix = matrix_utils.get_matrix(size, size)

	for i in range(0, size):
		matrix[i][i] = Decimal(2.0) + (Decimal(1.0) / (Decimal(size) ** Decimal(2.0)))

	for i in range(0, size - 1):
		matrix[i][i+1] = Decimal(-1)
		matrix[i+1][i] = Decimal(-1)
	
	b_array = [Decimal(1.0) / (Decimal(size) ** Decimal(2.0)) for i in range(0, size)]

	return matrix, b_array

def solve(size):
	matrix, b_array = create_input(size)
	
	norma_infinit = jacobi_relaxata_copy.get_norma_infinit(matrix)
	jacobi_relaxata_copy.main_loop(matrix, size, norma_infinit, b_array)

	# gradient.GC(matrix, len(matrix), b_array)
	
	# gauss.GS(matrix, len(matrix), len(matrix), b_array)


if __name__ == '__main__':
	solve(10)