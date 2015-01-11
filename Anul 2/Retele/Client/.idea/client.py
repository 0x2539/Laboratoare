__author__ = 'Alexandru'
import socket
import sys
import signal
import time
import os
from math import ceil

sock = None
class TimeLimitExpired(Exception): pass

def timelimit(timeout, func):
    """ Run func with the given timeout. If func didn't finish running
        within the timeout, raise TimeLimitExpired
    """
    import threading
    class FuncThread(threading.Thread):
        def __init__(self):
            threading.Thread.__init__(self)
            self.result = None

        def run(self):
            self.result = func()

    it = FuncThread()
    it.start()
    it.join(timeout)
    if it.isAlive():
        raise TimeLimitExpired()
    else:
        return it.result

def ceildiv(a, b):
    return -(-a // b)

def send_packet(message, bit):
    # Send data
    print 'sent packet:', message
    sock.sendall(message)

    # Look for the response
    amount_received = 0
    amount_expected = len(message)

    data = ''

    while amount_received < amount_expected:
        data += sock.recv(5)
        amount_received += len(data)

    if data == message and data[-1] == bit:
        print 'received packet:', data
        return True
    else:
        print 'didn\'t receive all data:', data
        return False

def send_message(message):
    # Send data
    print 'sending messsage:', message
    #sock.sendall(message)

    # Look for the response
    amount_received = 0
    amount_expected = len(message)

    data = ''
    bits = [str(x % 2) for x in range(0, int(ceildiv(len(message), 4)))]

    for i in range(0, int(ceildiv(len(message), 4))):
        sent = False
        while not sent:
            sent = send_packet(message[i*4:min(i*4+4, len(message))] + bits[i], bits[i])


def init_connection():
    # Create a TCP/IP socket
    global sock
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

    # Connect the socket to the port where the server is listening
    server_address = ('localhost', 8001)
    print 'connecting to %s port %s' % server_address
    sock.connect(server_address)


def run_client():
    global sock
    try:
        with open('C:\Users\Alexandru\Documents\Client\messages.txt', 'r') as file:
            messages = file.readlines()
            for message in messages:
                print ''
                send_message(message.strip())
    finally:
        print 'closing socket'
        sock.close()

init_connection()
timeout_ct = 10
timelimit(timeout_ct, run_client)




# def wait():
#     time.sleep(2)
#
# try:
#     timelimit(1, wait)
# except:
#     print 'timeout'