/* 
 * Authors: Daniel, Rebecca, Aaron
 *
 * Measurement overhead: Report the overhead of reading time, and report the overhead of using a loop to measure many iterations of an operation.
 */

#include <stdio.h>
#include <inttypes.h>
#include "measuretime.c"

void readTimeOverhead() {
   printf("\n================================");
   printf("\nRead Time Overhead Experiments.\n");
   
   int totalExperiments = 10;
   int runsPerExp = 1000000;
   float results[totalExperiments];

   int expNo, i;
   uint64_t strt, end, total, aggregate = 0;

   // Simulate experiments.
   for (expNo = 0; expNo < totalExperiments; ++expNo) {
      strt  = 0;
      end   =  0;
      total = 0;

      for (i=0; i<runsPerExp; ++i) {
         strt = rdtsc();
         end = rdtsc();
         total += end - strt;
      }

      // Output experiment stats.
      total /= runsPerExp;
      results[expNo] = total;
      aggregate += total;
      printf("ExpNo(%d) Total (%" PRIu64 ")\n", expNo, total);
   }

   printf("Aggregate Stats: Avg(%" PRIu64 ") STD(%f)\n", aggregate / (uint64_t)expNo, std(results, totalExperiments) );
}

void loopOverhead() {
   printf("\n================================");
   printf("\nLoop  Overhead Experiments.\n");
   
   int totalExperiments = 10;
   int runsPerExp = 1000000;
   float results[totalExperiments];

   int expNo, i;
   uint64_t strt, end;
   float total, aggregate = 0;

   // Simulate experiments.
   for (expNo = 0; expNo < totalExperiments; ++expNo) {
      strt  = 0;
      end   =  0;
      total = 0;

      strt = rdtsc();
      for (i=0; i<runsPerExp; ++i) { }
      end = rdtsc();

      total = (end - strt) / runsPerExp;
      results[expNo] = total;
      aggregate += total;

      printf("ExpNo(%d) Total (%f)\n", expNo, total);
   }

   printf("Aggregate Stats: Avg(%f) STD(%f)\n", aggregate/expNo, std(results, totalExperiments) );
}


int main() {
   readTimeOverhead();
   loopOverhead();
   return 0;
}
