#
# Final Project | CSE 221 | Spring 2018 | UCSD
#
# 4.3.3 - Connection overhead client code
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

# ======================CONNECTION OVERHEAD MEASUREMENT======================
# Start the clock!
setup_start = time.time() * S_TO_MS

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

# Done setting up
setup_end = time.time() * S_TO_MS

# Start tearing down
teardown_start = time.time() * S_TO_MS

sock.shutdown(socket.SHUT_RDWR)
sock.close()

teardown_end = time.time() * S_TO_MS
print "Closing client socket"

# Announce results
print "Connection setup = %f ms" %(setup_end - setup_start)
print "Connection teardown = %f ms" %(teardown_end - teardown_start)

exit(0)
