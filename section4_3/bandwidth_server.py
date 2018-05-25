#
# Final Project | CSE 221 | Spring 2018 | UCSD
#
# 4.3.2 - Bandwidth measurement server code
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

# ======================PEAK BANDWIDTH MEASUREMENT======================
try:
    print "Received a packet from: (%s, %s)" %(client_addr)

    total_received_len = 0
    total_time = 0

    # Set up some data for the end time
    received_len = 0

    # Accept first ACK
    ack = connection.recv(3)
    print "Received first ack from client: %s" %(ack)

    # Start the clock for this iteration of receiving
    start = time.time()

    # Receive one iteration
    while received_len < BWD_MSG_LEN_B:
        # Receive some data
        data = connection.recv(BWD_MSG_LEN_B)

        # print "Recieved some data: %s" % data

        # Increment the amount you've received
        received_len += sys.getsizeof(data)
    # End one iter recv

    # Record the end time after receiving all data for this iteration
    end = time.time()

    total_received_len += 1

    # print "total_received_len is %s" %(total_received_len)

    # Send an ack
    connection.sendall("ACK")

    # Want the peak possible bandwidth, so take the shortest time recorded
    total_time += end - start

finally:
    # Clean up the connection
    sock.close()

print "\tTotal time was %f s" %(total_time)
print "\tBandwidth is %f MB/s" %(MB_SENT / total_time)



















exit(0)
