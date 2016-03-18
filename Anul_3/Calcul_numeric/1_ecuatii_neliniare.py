import math
from decimal import *

interval_start = 0
interval_end = 3
nr_of_decimals = 24

def func(x):
	getcontext().prec = nr_of_decimals
	# return 4 * math.exp(-x) * math.sin(6 * x * math.sqrt(x)) - 1.0/5.0
	return Decimal(4) * Decimal(-x).exp() * Decimal(math.sin(6 * x * Decimal(math.sqrt(x)))) - Decimal(1.0)/Decimal(5.0)

def func_der(x):
	getcontext().prec = nr_of_decimals
	val = Decimal(4) * Decimal(-x).exp() * (Decimal(math.cos(Decimal(6) * Decimal(x) * Decimal(math.sqrt(x)))) * Decimal(9) * Decimal(math.sqrt(x)) - Decimal(math.sin(Decimal(6) * Decimal(x) * Decimal(math.sqrt(x)))))
	return val
	# return 4 * math.exp(-x) * math.sin(6 * x * math.sqrt(x)) - 1.0/5.0
	# return Decimal(4) * Decimal(-x).exp() * Decimal(math.sin(6 * x * Decimal(math.sqrt(x)))) - Decimal(1.0)/Decimal(5.0)

def solve_interval_coardei(a, b):
	getcontext().prec = nr_of_decimals
	if func(a) * func(b) >= 0:
		print 'start false', a, b
		print ''
		return False
	n = 0
	result = 0
	sigma = Decimal(0.000004)
	print 'start', a, b
	x0 = a
	x = b
	while math.fabs(Decimal(func(x))) > sigma: # and n < 100:
		x = (x0 * func(x) - x * func(x0)) / (func(x) - func(x0))
		
	print 'end', x
	print ''
	return True

def solve_interval_newton(a, b):
	getcontext().prec = nr_of_decimals
	if func(a) * func(b) >= 0:
		# print 'start false', a, b
		# print ''
		return False
	n = 0
	result = 0
	sigma = Decimal(0.0004)
	print 'start', a, b
	x0 = a
	x = b
	n = 0
	while math.fabs(Decimal(func(x))) > sigma and n < 300:
		x = x - (func(x0) / (func_der(x)))
		n += 1

	print 'end', x
	print ''
	return True

def solve_interval_secantei(a, b):
	getcontext().prec = nr_of_decimals
	if func(a) * func(b) >= 0:
		# print 'start false', a, b
		# print ''
		return False
	n = 0
	result = 0
	sigma = Decimal(0.000004)
	print 'start', a, b
	x0 = a
	x = b
	while math.fabs(Decimal(func(x))) > sigma: # and n < 100:
		x = (x0 * func(x) - x * func(x0)) / (func(x) - func(x0))
		
	print 'end', x
	print ''
	return True

def solve_interval(a, b, c):
	getcontext().prec = nr_of_decimals
	if func(a) * func(b) >= 0:
		# print 'start false', a, b, c
		# print ''
		return False
	n = 0
	result = 0
	sigma = Decimal(0.000004)
	print 'start', a, b
	while a < b and math.fabs(Decimal(func(c))) > sigma: # and n < 100:
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
	print 'end', c
	print ''
	return True

def solve_all_intervals():
	getcontext().prec = nr_of_decimals
	x = 0
	intervals = 64
	pase = Decimal(3) / Decimal(intervals)
	n = 0

	while n < intervals:
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