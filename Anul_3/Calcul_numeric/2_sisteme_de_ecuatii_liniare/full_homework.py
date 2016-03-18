import matrix_utils
import sisteme_de_ecuatii_liniare_Cholesky
import sisteme_de_ecuatii_liniare_LU
import sisteme_de_ecuatii_liniare_QR

def solve(n, p):
	matrix = matrix_utils.generate_combinations_matrix(n, p)

	b_array = [1 for i in range(len(matrix))]
	l_matrix, u_matrix = sisteme_de_ecuatii_liniare_LU.get_LU_matrices(matrix)
	y_matrix = sisteme_de_ecuatii_liniare_LU.get_Y_matrix(matrix, b_array, l_matrix)
	x_matrix = sisteme_de_ecuatii_liniare_LU.get_X_matrix(matrix, y_matrix, u_matrix)
	print x_matrix

	r_matrix, q_matrix = sisteme_de_ecuatii_liniare_QR.initial_init(matrix)
	r_matrix, q_matrix = sisteme_de_ecuatii_liniare_QR.prop_14(matrix, r_matrix, q_matrix)
	y = sisteme_de_ecuatii_liniare_QR.find_y_solution(matrix, q_matrix, b_array)
	x = sisteme_de_ecuatii_liniare_QR.find_x_solution(matrix, r_matrix, y)

	print x

	# cholesky_l_matrix = sisteme_de_ecuatii_liniare_Cholesky.get_L_matrix(matrix)
	# cholesky_y_matrix = sisteme_de_ecuatii_liniare_Cholesky.get_y_matrix(matrix, b_array)
	# cholesky_x_matrix = sisteme_de_ecuatii_liniare_Cholesky.get_y_matrix(cholesky_l_matrix, cholesky_y_matrix, b_array)
	# print cholesky_x_matrix

n = 5
p = 10
solve(n, p)