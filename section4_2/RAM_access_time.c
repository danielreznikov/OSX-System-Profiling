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
   //printf("\n\tTOTAL(%lf)", total);
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
   /* DELETE ME */
   exit(1);
}


/* 4.2.1 - RAM Access Time */
void _old_measure_RAM_access(uint64_t experiments, uint64_t iterations) {
   double result, avg, std;
   int i, expNo, arr_sz_idx, stride_sz, arr_sz;

   // Array sizes, 20 values representing 1KB->512MB arrays.
   int OneKB = 1024;
   int L1_SIZE = 32 * OneKB;        // 32KB
   int L2_SIZE = 256 * OneKB;       // 256KB
   int L3_SIZE = 6 * OneKB * OneKB; // 6MB
   int num_sizes = 20;
   int arr_sizes[num_sizes];
   for (i = 0; i < num_sizes; i++) {
      arr_sizes[i] = OneKB * pow(2, i);
   }
   
   // Stride parameter used in array traversal.
   int L1_STRIDE = 10;                               // 10B
   int L2_STRIDE = 64*OneKB/sizeof(int) ;            // 64KB
   int L3_STRIDE = OneKB * OneKB / sizeof(int);      // 1MB
   int L4_STRIDE = 10 * OneKB * OneKB / sizeof(int); // 10MB

   printHeader("4.2.1 - RAM Access Time");

   // Loop over array size experiments.
   for (arr_sz_idx = 0; arr_sz_idx < num_sizes; arr_sz_idx++) {
      // Instantiate an array of appropriate size.
      arr_sz = arr_sizes[arr_sz_idx];
      int *arr = (int*)malloc(arr_sz*sizeof(int));
      prepare_array(arr, arr_sz);

      // Set appropriate stride for region of memory.
      if (arr_sz < L1_SIZE)
         stride_sz = L1_STRIDE;
      else if (arr_sz < L2_SIZE)
         stride_sz = L2_STRIDE;
      else if (arr_sz < L3_SIZE)
         stride_sz = L3_STRIDE;
      else 
         stride_sz = L4_STRIDE;

      result = experiment_iter(arr, arr_sz, iterations, stride_sz);

      printf("\nARRAY_SIZE(%dKB), STRIDE(%d), CYCLES(%lf)\n", arr_sz/OneKB, stride_sz, result);

      free(arr);


   }
   /* DELETE ME */
   exit(1);
}


uint64_t _old_experiment_iter(int *arr, int arr_sz, uint64_t iterations, int stride_sz) {
   uint64_t total, strt, end;
   int idx, ptr = 0;

   strt = rdtsc();

   for (int i = 0; i < iterations; i++) {
      idx = (ptr + stride_sz) % arr_sz;
      ptr = arr[idx];
   }

   end = rdtsc();

   total = (end - strt);
   total /= iterations;
   total = total - 2* READ_TIME_OVERHEAD - LOOP_OVERHEAD;
   return total;
}
