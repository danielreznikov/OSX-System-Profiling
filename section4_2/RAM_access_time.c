/*
 * Final Project | CSE 221 | Spring 2018 | UCSD
 *
 * 4.2.1 - Measure the time for a RAM access.
 */
#include "../utils.h"
#include "driver_2.h"
#define ARRAY_SIZE  1000000

/* Helper method to initialize an array of pointers*/
void prepare_array(int *arr, int stride_sz)  {
   for(int i = 0; i < ARRAY_SIZE; i++) {
      // use of stride size taken from lmbench paper
      arr[i] = i + stride_sz;
   }
}

/* Execute a single experiment, returns avg cycle latency of reading an integer */
uint64_t experiment_iter(int *arr, uint64_t iterations) {
   uint64_t total, strt, end;
   int ptr = 0;

   strt = rdtsc();

   for (int i = 0; i < iterations; i++) {
      ptr = arr[ptr + i];
   }

   end = rdtsc();

   total = (end - strt) -  2*READ_TIME_OVERHEAD;
   total /= iterations;
   total -= LOOP_OVERHEAD;
   return total;
}

/* 4.2.1 - RAM Access Time */
void measure_RAM_access(uint64_t experiments, uint64_t iterations) {
   uint64_t total, res;
   int strides[] = {1, 2, 4, 16, 32, 64, 128, 256, 512, 1024};
   int len = sizeof(strides) / sizeof(int);
   double results[experiments];
   double avg, std;

   printHeader("4.2.1 - RAM Access Time");

   for (int i = 0; i < len; i++) {
      int arr[ARRAY_SIZE];
      prepare_array(arr, strides[i]);

      for (int expNo = 0; expNo < experiments; expNo++) {
         res = experiment_iter(arr, iterations);
         results[expNo] = (double)res;
         total += res;
      }

      stats(results, experiments, &avg, &std);

      printf("\nstride(%d) total(%-9" PRIu64 ") avg(%f) std(%f) \n", strides[i], total, avg, std);

   }


}

