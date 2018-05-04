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

/* Measure the reading bandwidth with SSE intrinsics */
void measure_RAM_reading_bandwidth(uint64_t experiments, uint64_t iterations) {
    uint64_t start, end, arr_ndx, iter, exper;
    uint8_t *src_arr, *dest_arr;
    __m128i dest;
    double time_sec, iter_total, iter_band, data_read_gb;
    double avg, std, exper_total, results[experiments];

    printHeader("4.2.2 - RAM Reading Bandwidth (GB/s)");

    /* Allocate two large aligned arrays into main memory */
    posix_memalign((void **)(&src_arr), ALIGNMENT, DEST_SIZE_B);
    memset(src_arr, 0xAA, DEST_SIZE_B);
    posix_memalign((void **)(&dest_arr), ALIGNMENT, DEST_SIZE_B);
    memset(dest_arr, 0xBB, DEST_SIZE_B);


    /* Loop for the given number of experiments */
    for (exper = 0; exper < experiments; exper++) {
        iter_total = 0;

        /* Loop for the given number of iterations */
        for (iter = 0; iter < iterations; iter++) {

            /* Start the clock */
            start = rdtsc();

            /* Loop through the array in sizes bigger than the L3 cache */
            for (arr_ndx = 0; arr_ndx < DEST_SIZE_B; arr_ndx += L3_SIZE_B) {
                /*  */
                bcopy((void *)src_arr, (void *)dest_arr, L3_SIZE_B);
            }

            /* Stop the clock */
            end = rdtsc();

            /* Update the total time for this iteration */
            iter_total += end - start;

        } /* END ITERATION LOOP */

        // printf("iter_total is %lf cycles\n", iter_total);
        /* Divide by two as a rough estimate of the time spent on copying */
        iter_total /= 2;

        /* Store how much data you read in gigabytes */
        data_read_gb = DEST_SIZE_GB * iterations;
        // printf("read %lf gigabytes\n", data_read_gb);

        /* Calculate how long this experiment took in seconds */
        time_sec = iter_total / (double)SYS_MEM_FREQ;
        // printf("time for all iterations is: %lf\n", time_sec);

        /* Calculate the bandwidth of this iteration */
        iter_band = data_read_gb / time_sec;
        // printf("Bandwidth in GB/s: %lf\n", iter_band);

        /* Save into results array and print table entry */
        results[exper] = iter_band;
        printEntry(exper, iter_band);

    } /* END EXPERIMENT LOOP */

    /* Clean up */
    free(dest_arr);
    free(src_arr);

    /* Calculate statistics about all experiments */
    stats(results, experiments, &avg, &std);
    printStats(avg, std);
}

/* Measure the writing bandwidth with SSE intrinsics */
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
    /* Measure the writing bandwidth */
    measure_RAM_writing_bandwidth(experiments, iterations);

    /* Measure the reading bandwidth */
    measure_RAM_reading_bandwidth(experiments, iterations);
}
