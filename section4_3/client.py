import socket
import sys
import time
import numpy as np
from utils import *

# Fill in the message buffer with 64 bytes of ASCII
buf = bytearray()
for i in range(0, MSG_LEN_BYTES):
    buf.append(NUM_ASCII + i)

# Open up the socket using TCP IPv4
try:
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    print "Successfully created a socket"
except socket.error as error:
    print "Failed to create a socket: %s" %(error)

# Specify the port to communicate through
server_addr = ('', 59030)

# Listen for packets on this port on this network
try:
    sock.connect(server_addr)
    print "Successfully connected to port: (%s, %s)" %(server_addr)
except socket.error as error:
    print "Failed to connect to the port: %s" %(error)

printHeader("4.3.1 - (Local) Round Trip Time (ms)")

try:
    aggregate = []

    for exp in range(0, EXPERIMENTS):
        result = []

        # Loop for all iterations
        for iter in range(0, ITERATIONS):
            # Set up the data
            # print "Sending: %s" %(buf)

            # Start the timer
            start = time.time()

            # Send the message to the port
            sock.sendall(buf)

            # Set up some data for the response
            received_len = 0

            # Do the recieve
            while (received_len < MSG_LEN_BYTES):
                # Grab this data from the socket
                recv_data = sock.recv(MSG_LEN_BYTES)

                # Update the length
                received_len += len(recv_data)

                # Print out what you've recieved so far
                # print "Recieved data: %s" %(recv_data)

            end = time.time()

            # print "Total time recorded: %s seconds" %(end - start)

            result.append((end - start) * S_TO_MS)
        # End iter loop

        # print "Result of exp " + str(exp) + " is: " + str(result)

        # Calculate average and print to screen
        avg = np.mean(result)
        printEntry(exp, avg)

        # Save this experiment's average
        aggregate.append(avg)

    # End exp loop

    # Print the statistics of this experiment
    printStats(np.mean(aggregate), np.std(aggregate))


finally:
    sock.close()
    print "Closing client socket"
