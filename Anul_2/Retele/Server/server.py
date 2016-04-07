__author__ = 'Alexandru'
import socket
import sys
import time
import threading

sock = None
client_address = None
connection = None
no_more_data = False

# class TimeLimitExpired(Exception): pass
#
# def timelimit(timeout, func):
#     """ Run func with the given timeout. If func didn't finish running
#     within the timeout, raise TimeLimitExpired
#     """
#     class FuncThread(threading.Thread):
#         def __init__(self):
#             threading.Thread.__init__(self)
#             self.result = None
#
#         def run(self):
#             self.result = func()
#
#     it = FuncThread()
#     it.start()
#     it.join(timeout)
#     if it.isAlive():
#         raise TimeLimitExpired()
#     else:
#         return it.result

def init_server():
    # Create a TCP/IP socket
    global sock
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    sock.settimeout(2)
    sock.setblocking(1)

    # Bind the socket to the port
    server_address = ('localhost', 8001)
    print 'starting up on %s port %s' % server_address
    sock.bind(server_address)

    # Listen for incoming connections
    sock.listen(1)

def read_messages():
    global connection, no_more_data

    data = connection.recv(5)
    print 'received:', data
    if data:
        print 'sending data back to the client'
        connection.sendall(data)
    else:
        print 'no more data from:', client_address
        no_more_data = True
        #raise Exception('no more data from client')


def run_server():
    global client_address, connection, no_more_data
    timeout_st = 10

    while True:
        # Wait for a connection
        print 'waiting for a connection'
        connection, client_address = sock.accept()
        try:
            print 'connection from:', client_address

            # Receive the data in small chunks and retransmit it
            no_more_data = False
            while True and not no_more_data:
                read_messages()
                #timelimit(timeout_st, read_messages)

        except Exception, e:
            print e

        finally:
            # Clean up the connection
            print 'connection terminated'
            connection.close()

init_server()
run_server()