import math

def nCr(n, r):
	if r > n:
		return 0

	f = math.factorial
	return f(n) / f(r) / f(n-r)

def get_matrix_transpose(matrix):
	return [list(x) for x in zip(*matrix)]

def det2(l):
	n=len(l)
	if (n>2):
		i=1
		t=0
		sum=0
		while t<=n-1:
			d={}
			t1=1
			while t1<=n-1:
				m=0
				d[t1]=[]
				while m<=n-1:
					if (m==t):
						u=0
					else:
						d[t1].append(l[t1][m])
					m+=1
				t1+=1
			l1=[d[x] for x in d]
			sum=sum+i*(l[0][t])*(det2(l1))
			i=i*(-1)
			t+=1
		return sum
	elif n == 2:
		return (l[0][0]*l[1][1]-l[0][1]*l[1][0])
	elif n == 1:
		return l[0][0]

# from copy import deepcopy
# def minor(matrix,i):
#     """Returns the Minor M_0i of matrix"""
#     minor = deepcopy(matrix)
#     del minor[0] #Delete first row
#     for b in list(range(len(matrix))): #Delete column i
#         del minor[b][i]
#     return minor

# def det(A):
#     """Recursive function to find determinant"""
#     if len(A) == 1: #Base case on which recursion ends
#         return A[0][0]
#     else:
#         determinant = 0
#         for x in list(range(len(A))): #Iterates along first row finding cofactors
#             print("A:", A)
#             determinant += A[0][x] * (-1)**(2+x) * det(minor(A,x)) #Adds successive elements times their cofactors
#             print("determinant:", determinant)
#         return determinant

# data = [[4, 3], [6, 3]]

res = [0.0910140527, 0.32479293, 0.700278532, 1.1791699, 1.725370323, 2.2946296, 2.84083002, 3.319721467, 3.69250706, 3.9289859472]

def get_matrix(size, fill_value=0):
	"""
	Creates an empty matrix with n lines and n columns, n == size
	"""
	return [[fill_value for i in range(size)] for i in range(size)]

def get_matrix(size_line, size_col, fill_value=0):
	"""
	Creates an empty matrix with n lines and n columns, n == size
	"""
	return [[fill_value for i in range(size_col)] for i in range(size_line)]

def get_determinant(matrix, max_line_col):
	"""
	Given a matrix n by n size, it calculates the determinant of the top left matrix with m by m size, m == max_line_col
	"""
	if max_line_col > len(matrix):
		print 'line and col are higher than the matrix size'
		return

	# init matrix
	new_matrix = get_matrix(max_line_col)

	for i in range(0, max_line_col):
		for j in range(0, max_line_col):
			new_matrix[i][j] = matrix[i][j]

	# get determinant
	return det2(new_matrix)
	# return det(new_matrix)
	# return numpy.linalg.det(new_matrix)
	# sign, logdet = numpy.linalg.slogdet(new_matrix)
	# det = numpy.exp(logdet)
	# return sign * det

def check_determinanti_de_colt_nenul(matrix):
	k = 1
	while k <= len(matrix):
		print 'det', get_determinant(matrix, k)
		if get_determinant(matrix, k) == 0:
			print 'determinant de colt nul, cu k: %s si valoare %s' % (str(k), str(get_determinant(matrix, k)))
			return False
		k += 1
	return True

def check_determinanti_de_colt_positive(matrix):
	k = 1
	while k <= len(matrix):
		print 'det', get_determinant(matrix, k)
		if get_determinant(matrix, k) > 0:
			print 'determinant de colt nul, cu k: %s si valoare %s' % (str(k), str(get_determinant(matrix, k)))
			return False
		k += 1
	return True

def generate_combinations_matrix(n, p):
	matrix = get_matrix(n)

	for i in range(n):
		for j in range(n):
			# TODO which one to choose???? first one is the one from the homework, but i < p+j and that's wrong
			# matrix[i][j] = nCr(i, p + j)
			matrix[i][j] = nCr(p + j, i)
			# matrix[i][j] = nCr(p + j, i)

	return matrix
