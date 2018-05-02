/*
 * Final Project | CSE 221 | Spring 2018 | UCSD
 *
 * 4.2.2 - Measure the RAM bandwidth ability.
 */
#include "../utils.h"
#include "driver_2.h"

/* Constants */
/* Destination size in 16 bytes */
#define DEST_SIZE       500000
#define SIZE_128_BYTES  16
#define BYTES_TO_MBYTES 0.000001

/* 4.2.2 - RAM Bandwidth */
void measure_RAM_bandwidth(uint64_t experiments, uint64_t iterations) {
    uint64_t iter = 0, exper = 0, start, end, exp_total = 0;
    double g_total, cyc_results[experiments];
    double band_results[experiments], time_sec;
    double cyc_avg, cyc_std, band_avg, band_std;

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
        cyc_results[exper] = g_total;

        /* Print out this experiment's entry */
        printEntry(exper, (double)g_total);

        /* Calculate and save the MB/s bandwidth */
        time_sec = (double)g_total / (double)SYS_MEM_FREQ;
        band_results[exper] = (BYTES_TO_MBYTES * (double)SIZE_128_BYTES) / time_sec;
    }

    /* Calculate the average cycles across all experiments */
    stats(cyc_results, experiments, &cyc_avg, &cyc_std);
    printStats(cyc_avg, cyc_std);

    /* Calculate the average MB/s across all experiments */
    stats(band_results, experiments, &band_avg, &band_std);
    printStats(band_avg, band_std);





























}
