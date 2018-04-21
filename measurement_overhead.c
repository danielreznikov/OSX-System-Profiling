/* 
 * Authors: Daniel, Rebecca, Aaron
 *
 * Measurement overhead: Report the overhead of reading time, and report the overhead of using a loop to measure many iterations of an operation.
 */

#include <stdio.h>
#include <inttypes.h>
#include "measuretime.c"

void readTimeOverhead() {
   printf("================================");
   printf("\nRead Time Overhead Experiments.\n");
   
   int expNo = 0;
   uint64_t strt, end, total, aggregate = 0;
   int i = 0;

   for (; expNo < 10; ++expNo) {
      strt  = 0;
      end   =  0;
      total = 0;

      for (i = 0; i < 1000000; ++i) {
         strt = rdtsc();
         end = rdtsc();
         total += end - strt;
      }

      // Output experiment stats.
      total /= 1000000;
      aggregate += total;
      printf("ExpNo(%d) Total (%" PRIu64 ")\n", expNo, total);
   }

   printf("Aggregate Stats: Avg(%" PRIu64 ") STD()\n", aggregate/(uint64_t)expNo );
}

void loopOverhead() {
}


int main() {
   readTimeOverhead();
   return 0;
}
