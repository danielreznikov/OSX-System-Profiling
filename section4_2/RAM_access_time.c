/*
 * Final Project | CSE 221 | Spring 2018 | UCSD
 *
 * 4.2.1 - Measure the time for a RAM access.
 */
#include "../utils.h"
#include "driver_2.h"

/* Helper method to initialize an array of pointers */
void prepare_array(int *arr, int arr_sz)  {
   for(int i = 0; i < arr_sz; i++) {
      arr[i] = i;
   }
}

/* Execute a single experiment, returns avg cycle latency of reading an integer */
double experiment_iter(int *arr, int arr_sz, uint64_t iterations, int stride_sz) {
   uint64_t result, strt, end;
   int i, j, idx, randm, ptr = 0;
   double total;
   
   strt = rdtsc();

   // An iteration is a single ptr update.
   for (i = 0; i < iterations; i++) {
      idx = (ptr + stride_sz) % arr_sz;
      ptr = arr[idx];
      //printf("\n\tIDX(%d)", idx);
   }

   end = rdtsc();

   result = end - strt;
   total = (double)result / (double)iterations;
   //total = total - 2 * READ_TIME_OVERHEAD - LOOP_OVERHEAD;
   return total;
}

/* 4.2.1 - RAM Access Time */
void measure_RAM_access(uint64_t experiments, uint64_t iterations) {
   double total, avg, std, res;
   int i, expNo, arr_sz_idx, stride_sz, arr_sz;
   double results[experiments];

   // Array sizes, 20 values representing 1KB->512MB arrays.
   int OneKB = 1024;
   int num_sizes = 20;
   int arr_sizes[num_sizes];
   int stride_sizes[num_sizes];
   for (i = 0; i < num_sizes; i++) {
      arr_sizes[i] = OneKB * pow(2, i);
      stride_sizes[i] = 10 * pow(2, i);
   }
   
   printHeader("4.2.1 - RAM Access Time");

   // Loop over stride sizes.  
   for (int stride_idx = 0; stride_idx < num_sizes; stride_idx++) {
      stride_sz = stride_sizes[stride_idx];
      printf("\nSTRIDE_SIZE(%d)", stride_sz);

      // Loop over array size experiments.
      for (arr_sz_idx = 0; arr_sz_idx < num_sizes; arr_sz_idx++) {
         // Instantiate an array of appropriate size.
         arr_sz = arr_sizes[arr_sz_idx];
         int *arr = (int*)malloc(arr_sz*sizeof(int));
         prepare_array(arr, arr_sz);

         // Loop over experiments for statistical precision.
         for (expNo = 0; expNo < experiments; expNo++) {
            res = experiment_iter(arr, arr_sz, iterations, stride_sz);
            results[expNo] = res;
         }
         stats(results, experiments, &avg, &std);
         printf("\n\tARRAY_SIZE(%luKB), AVG(%lf), STD(%f) \n", arr_sz/(long)OneKB, avg, std);

         free(arr);
      }
   }
}
