#
# Final Project | CSE 221 | Spring 2018 | UCSD
#
# 4.3.2 - Bandwidth measurement client code
#

#============================CLIENT CODE============================
import socket
import sys
import time
import numpy as np
from utils import *

# Grab the server IP
if (len(sys.argv) < 2):
    print "Need to enter a valid IP address"
    exit(ERR)

server_ip = sys.argv[1]
print "Server's IP: %s" %(server_ip)

# Open up the socket using TCP IPv4
try:
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    print "Successfully created a socket"
except socket.error as error:
    print "Failed to create a socket: %s" %(error)
    exit(ERR)

# Specify the port to communicate through
server_addr = (server_ip, PORT)

# Listen for packets on this port on this network
try:
    sock.connect(server_addr)
    print "Successfully connected to port: (%s, %s)" %(server_addr)
except socket.error as error:
    print "Failed to connect to the port: %s" %(error)
    exit(ERR)

# ======================PEAK BANDWIDTH MEASUREMENT======================
# Fill in the message buffer with many bytes of ASCII
buf = bytearray()
for i in range(0, BWD_MSG_LEN_B):
    buf.append('m')

try:
    # Send the first hello ACK
    print "About to send the first ACK"
    sock.sendall("ACK")

    # Send the message to the port
    print "About to send buf"
    sock.sendall(buf)

    received_len = 0
    # Recv the ack
    while (received_len < ACK_LEN_B):
        # Grab this data from the socket
        recv_data = sock.recv(ACK_LEN_B)

        # Update the length
        received_len += len(recv_data)

        # Print out what you've recieved so far
        # print "Recieved data: %s" %(recv_data)

# End iter loop

finally:
    sock.shutdown(socket.SHUT_RDWR)
    sock.close()
    print "Closing client socket"

exit(0)
