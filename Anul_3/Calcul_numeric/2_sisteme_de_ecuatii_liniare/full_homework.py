import matrix_utils
import sisteme_de_ecuatii_liniare_Cholesky
import sisteme_de_ecuatii_liniare_LU
import sisteme_de_ecuatii_liniare_QR

def solve(n, p):
	matrix = matrix_utils.generate_combinations_matrix(n, p)

n = 10
p = 20
solve(n, p)