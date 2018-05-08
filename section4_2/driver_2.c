/*
 * Final Project | CSE 221 | Spring 2018 | UCSD
 *
 * Main driver file for 4.2 - Memory Measurements.
 */

#include "driver_2.h"

/* Main driver and formatting for project output */
int main() {
    printf("==========CSE 221 Final Project Measurements - Section 4.2==========\n");

    /* 4.2.1 - RAM Access Time */
    //measure_RAM_access(EXPERIMENTS, ITERATIONS);

    /* 4.2.2 - RAM Bandwidth */
    //measure_RAM_bandwidth(EXPERIMENTS, ITERATIONS);

    /* 4.2.3 - Page Fault Service Time */
    measure_page_fault(EXPERIMENTS, ITERATIONS);

    return 0;
}
