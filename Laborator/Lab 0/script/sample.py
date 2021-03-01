from socket import *

sock = socket(AF_INET, SOCK_STREAM)
sock.connect(('127.0.0.1', 40000))
sock.send(b'time NaN')
sock.close()