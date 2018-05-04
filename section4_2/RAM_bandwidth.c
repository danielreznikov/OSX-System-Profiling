/*
 * Final Project | CSE 221 | Spring 2018 | UCSD
 *
 * 4.2.2 - Measure the RAM bandwidth ability.
 */
#include "../utils.h"
#include "driver_2.h"

/* Constants */
#define ALIGNMENT       16
#define DEST_SIZE_B     1073741824
#define BYTES_TO_GBYTES 1073741824
#define DEST_SIZE_GB    (double)DEST_SIZE_B / (double)BYTES_TO_GBYTES

void measure_RAM_writing_bandwidth(uint64_t experiments, uint64_t iterations) {
    __m128i src;
    uint8_t *dest_arr;
    uint64_t iter, arr_ndx, exper;
    double start, end, iter_total, time_sec, iter_band;
    double avg, std, exper_total, results[experiments];

    printHeader("4.2.2 - RAM Writing Bandwidth (GB/s)");

    /* Allocate a large aligned array into main memory */
    posix_memalign((void **)(&dest_arr), ALIGNMENT, DEST_SIZE_B);
    memset(dest_arr, 0xAA, DEST_SIZE_B);

    /* Set the source value to store into the array */
    src = _mm_set_epi64x(0xDEADBEEF, 0xDEADBEEF);

    /* Loop for the given number of experiments */
    for (exper = 0; exper < experiments; exper++) {
        iter_total = 0;

        /* Loop for the given number of iterations */
        for (iter = 0; iter < iterations; iter++) {

            /* Start the timer */
            start = rdtsc();

            /* Loop through the large array and store unique values into it */
            for (arr_ndx = 0; arr_ndx < DEST_SIZE_B; arr_ndx += sizeof(__m128i)) {

                /* Use the non-temporal intrinsics to avoid caching */
                _mm_stream_si128((__m128i *)(dest_arr + arr_ndx), src);

                /* Update the src value to avoid caching */
                src = _mm_add_epi64(src, src);
            }

            /* End the timer */
            end = rdtsc();

            /* Record and increment this iteration's value */
            iter_total += end - start;

        } /* END ITERATION LOOP */

        /* Calculate how long this experiment took in seconds */
        time_sec = iter_total / (double)SYS_MEM_FREQ;
        // printf("time for all iterations is: %lf\n", time_sec);

        iter_band = (DEST_SIZE_GB * iterations) / time_sec;
        // printf("Bandwidth in GB/s: %lf\n", iter_band);

        /* Save into results array and print table entry */
        results[exper] = iter_band;
        printEntry(exper, iter_band);

    } /* END EXPERIMENT LOOP */

    /* Clean up */
    free(dest_arr);

    /* Calculate statistics about all experiments */
    stats(results, experiments, &avg, &std);
    printStats(avg, std);
}

/* 4.2.2 - RAM Bandwidth */
void measure_RAM_bandwidth(uint64_t experiments, uint64_t iterations) {
    measure_RAM_writing_bandwidth(experiments, iterations);
}
