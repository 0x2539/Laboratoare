import math
from decimal import *

interval_start = 0
interval_end = 3
nr_of_decimals = 24

def func(x):
	getcontext().prec = nr_of_decimals
	# return 4 * math.exp(-x) * math.sin(6 * x * math.sqrt(x)) - 1.0/5.0
	return Decimal(4) * Decimal(-x).exp() * Decimal(math.sin(6 * x * Decimal(math.sqrt(x)))) - Decimal(1.0)/Decimal(5.0)

def solve_interval(a, b, c):
	getcontext().prec = nr_of_decimals
	if func(a) * func(b) >= 0:
		print 'start false', a, b, c
		print ''
		return False
	n = 0
	result = 0
	print 'start', a, b, c
	while a < b and n < 100:
		result = Decimal(func(a)) * Decimal(func(c))
		n += 1
		if func(c) == 0:
			break
		if result > 0:
			a = c
			# c = Decimal(a + b) / Decimal(2)
			c = (Decimal(a) * Decimal(func(b)) - Decimal(b) * Decimal(func(a))) / (Decimal(func(b)) - Decimal(func(a)))
		elif result < 0:
			b = c
			# c = Decimal(a + b) / Decimal(2)
			c = (Decimal(a) * Decimal(func(b)) - Decimal(b) * Decimal(func(a))) / (Decimal(func(b)) - Decimal(func(a)))
		else:
			break
	print 'end', result, a, b, c, n
	print ''
	return True

def solve_all_intervals():
	getcontext().prec = nr_of_decimals
	x = 0
	pase = Decimal(1) / Decimal(4)
	n = 0

	while n < 12:
		a = x
		b = x + pase
		c = (Decimal(a) * Decimal(func(b)) - Decimal(b) * Decimal(func(a))) / (Decimal(func(b)) - Decimal(func(a)))
		# c = Decimal(a + b) / Decimal(2)

		solve_interval(a, b, c)
		x += pase
		n += 1

a = interval_start
b = interval_end
# c = (a * func(b) - b * func(a)) / (func(b) - func(a))
c = Decimal(a + b) / Decimal(2)

solve_all_intervals()

print 'done', func(0)