__author__ = 'Alexandru'

def padd_bits_end(polynomial, message):
    for nr in polynomial:
        if nr == '1':
            message += '0'
    return message

def do_xor(first, second):
    new_xor = ''
    can = False
    # print first, second
    for i in range(0, len(first)):
        xor = str((int(first[i]) + int(second[i])) % 2)
        if xor == '1':
            can = True
        if can:
            new_xor += xor
    return new_xor

def get_crc(polynomial, message):
    index = 4
    last_part = message[:4]
    # print message
    crc = ''
    while index <= len(message):
        xor_elements = do_xor(last_part, polynomial)
        # print xor_elements, message[index : ], index, index + 4 - len(xor_elements)
        last_part = xor_elements + message[index : index + 4 - len(xor_elements)]
        index += 4 - len(xor_elements)
        crc = xor_elements
    zeros = '0'* (3-len(crc))
    crc = zeros + crc
    return crc


def main():
    polynomial = '1101'
    message = '010111001'
    message = padd_bits_end(polynomial, message)
    print get_crc(polynomial, message)
    new_message = '010111001'
    new_message += get_crc(polynomial, message)
    print get_crc(polynomial, new_message)

main()