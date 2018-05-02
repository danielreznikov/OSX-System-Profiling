/*
 * Final Project | CSE 221 | Spring 2018 | UCSD
 *
 * 4.2.2 - Measure the RAM bandwidth ability.
 */
#include "../utils.h"
#include "driver_2.h"

/* Constants */
/* Destination size in 16 bytes */
#define DEST_SIZE    400000

/* 4.2.2 - RAM Bandwidth */
void measure_RAM_bandwidth(uint64_t experiments, uint64_t iterations) {
    uint64_t iter = 0, exper = 0, start, end, exp_total = 0;
    double aggregate = 0.0, g_total, results[experiments], avg, std;

    /* Declare the destination array */
    __m128i* dest_addr = malloc(sizeof(__m128i) * DEST_SIZE);

    /* Set the source constant to some number */
    __m128i src = _mm_setr_epi32(0xDEAD, 0xBEEF, 0xDEAD, 0xBEEF);

    printHeader("4.2.2 - RAM Bandwidth");

    /* Run for multiple experiments */
    for (exper = 0; exper < experiments; exper++) {
        exp_total = 0;

        /* Run the loop for all iterations */
        for (iter = 0; iter < iterations; iter++) {
            /* Set up values for this iteration */
            dest_addr = malloc(sizeof(__m128i) * DEST_SIZE);

            /* Save the given value into this memory slot */
            start = rdtsc();
            _mm_stream_si128(dest_addr, src);
            end = rdtsc();

            /* Tear down values for this iteration */
            dest_addr = NULL;
            free(dest_addr);

            /* Add up the timing for all these iterations */
            exp_total += end - start;
        }

        /* Calculate the average time for that experiment */
        g_total = (double)exp_total / (double)iterations;
        aggregate += g_total;
        results[exper] = g_total;

        /* Print out this experiment's entry */
        printEntry(exper, (double)g_total);
        printEntry(exper, (double)g_total);
    }

    /* Calculate the average across all experiments */
    stats(results, experiments, &avg, &std);
    printStats((double)aggregate / (double)experiments, std);




























}
