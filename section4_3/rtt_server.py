#
# Final Project | CSE 221 | Spring 2018 | UCSD
#
# 4.3.1 - Round Trip Time server code
#

#============================SERVER CODE============================
# import socket
import socket
import sys
import time
from utils import *

# Open up the socket using TCP IPv4
try:
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    print "Successfully created a socket"
except socket.error as error:
    print "Failed to create a socket: %s" %(error)
    exit(ERR)

# Specify the port to communicate through
sock_hostname = ''
server_addr = (sock_hostname, PORT)

# Listen for packets on this port on this network
try:
    sock.bind(server_addr)
    print "Successfully binded to port: (%s, %s)" %(server_addr)
except socket.error as error:
    print "Failed to bind the socket: %s" %(error)
    exit(ERR)

# Block to let the socket listen for incoming packets - only allow one connection
try:
    sock.listen(1)
    print "Server is set to listen"
except socket.error as error:
    print "Socket failed to listen: %s" %(error)
    exit(ERR)

# Set up the connection
connection, client_addr = sock.accept()

# ======================ROUND TRIP TIME MEASUREMENT======================
try:
    # print "Received a packet from: (%s, %s)" %(client_addr)

    # Receive the data in small chunks and retransmit it
    while True:
        data = connection.recv(16)
        # print "Recieved the data: %s" % data

        if data:
            # Send the data back to the client
            connection.sendall(data)
        else:
            # print "No more data to receive from: (%s, %s)" %(client_addr)
            break

finally:
    # Clean up the connection
    connection.close()

print "Done with program"
