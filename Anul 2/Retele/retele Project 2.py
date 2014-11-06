def get_macs():
	with open('input.txt', 'r') as inf:
		my_bytes = inf.read()
		return my_bytes

def get_xor(byte1, byte2):
	return (byte1 + byte2) % 2

def xor(the_bytes):
	final_byte = 0
	for x in the_bytes:
		final_byte = get_xor(x, final_byte)
	return final_byte

def isPowerOfTwo(value):
	return value in [2**x for x in range(0, value)]

def codificare(the_bytes):
	final_bytes = []
	index = 1
	powersOfTwo = []

	i = 0
	while(i < len(the_bytes)):
		if isPowerOfTwo(index):
			final_bytes.append(0);
			powersOfTwo.append(index)
			i -= 1
		else:
			final_bytes.append(int(the_bytes[i]))
		index += 1
		i += 1

	for the_power_of_two in powersOfTwo:
		list_for_xor = []
		nrOfItems = the_power_of_two
		for xor_index in range(the_power_of_two - 1, len(final_bytes), the_power_of_two * 2):
			list_for_xor += final_bytes[xor_index : xor_index + the_power_of_two]
		final_bytes[the_power_of_two - 1] = xor(list_for_xor)

	print final_bytes

def decodificare(the_bytes):
	final_bytes = map(int, the_bytes)
	index = 1

	powersOfTwo = [x for x in range(0, len(the_bytes)) if isPowerOfTwo(x)]

	# i = 0
	# while(i < len(the_bytes)):
	# 	if isPowerOfTwo(index):
	# 		final_bytes.append(0);
	# 		powersOfTwo.append(index)
	# 		i -= 1
	# 	else:
	# 		final_bytes.append(int(the_bytes[i]))
	# 	index += 1
	# 	i += 1

	for the_power_of_two in powersOfTwo:
		list_for_xor = []
		nrOfItems = the_power_of_two
		for xor_index in range(the_power_of_two - 1, len(final_bytes), the_power_of_two * 2):
			list_for_xor += final_bytes[xor_index : xor_index + the_power_of_two]
		final_bytes[the_power_of_two - 1] = xor(list_for_xor)

	error_number = [final_bytes[x - 1] for x in powersOfTwo]
	error_number = error_number[::-1]
	binary_number = ''.join(map(str,error_number))
	decimal_number = int(binary_number, 2)
	print error_number, decimal_number


	print final_bytes

# def decodificare(the_bytes):
# 	highest_power_of_two = x for x in the_bytes if
	

def main():
	codificare('0110')
	decodificare('1100100')
	# decodificare('1100110')
	# xor("1110")

main()

#0110: 
#1
#1 1 0 0 1 1 0