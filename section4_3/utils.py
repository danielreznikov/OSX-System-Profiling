#
# Final Project | CSE 221 | Spring 2018 | UCSD
#
# File holding utility functions including printing, statistics measurement,
# and file writing for Python.
#
import sys

ACK_LEN_B       = 3
MB_SENT         = 300
B_TO_MB         = 1048576
BWD_MSG_LEN_B   = 1048576*MB_SENT
END_TIME_B      = 13
ERR             = -1
EXPERIMENTS     = 10
ITERATIONS      = 10
MSG_LEN_BYTES   = 64
NUM_ASCII       = 48
PORT            = 59030
S_TO_MS         = 1000

# Prints the header for the output table
def printHeader(title):
    print "\n==========%s==========" %(title)
    print "|==============|============|"
    print "|  Experiment  |  Overhead  |"
    print "|==============|============|"

# Prints a single entry of the output table
def printEntry(experimentNumber, entry):
    print "|%s%-8s| %s%-7.3lf|" %(' ' * 6, experimentNumber, ' ' * 4, entry)

# Prints the average and stdev in the format of the output table
def printStats(average, std):
    print "|--------------|------------|"
    print "|   Average    | %s%-8.3lf|" %(3 * ' ', average)
    print "|--------------|------------|"
    print "|   Std Dev    | %s%-8.3lf|" %(3 * ' ', std)
    print "|--------------|------------|"
