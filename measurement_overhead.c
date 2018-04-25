/*
 * Authors: Daniel, Rebecca, Aaron
 *
 * Measurement overhead: Report the overhead of reading time, and report the
 * overhead of using a loop to measure many iterations of an operation.
 */
#include "utils.c"

/* Measures the overhead for reading with rdtsc */
void readTimeOverhead(int experiments, int iterations) {
   double results[experiments];
   double avg, std;
   int expNo, i;
   uint64_t strt, end, total, aggregate = 0;

   /* Print the header */
   printHeader("4.1 - Measurement Overhead");

   /* Simulate experiments */
   for (expNo = 0; expNo < experiments; ++expNo) {
      strt  = 0;
      end   =  0;
      total = 0;

      for (i = 0; i < iterations; ++i) {
         strt = rdtsc();
         end = rdtsc();
         total += end - strt;
      }

      /* Output experiment stats */
      total /= iterations;
      results[expNo] = total;
      aggregate += total;

      /* Print this output entry */
      printEntry(expNo, total);
   }

   /* Print average and stdev */
   stats(results, experiments, &avg, &std);
   printStats((double)aggregate / (double)expNo, std);
}

/* Measure the overhead of using a loop */
void loopOverhead(int experiments, int iterations) {
   double results[experiments];
   double avg, std;
   int expNo, i;
   uint64_t strt, end;
   double total, aggregate = 0;

   /* Print the header */
   printHeader("4.1 - Loop Overhead");

   /* Simulate experiments */
   for (expNo = 0; expNo < experiments; ++expNo) {
      strt  = 0;
      end   =  0;
      total = 0;

      strt = rdtsc();
      for (i = 0; i < iterations; ++i) { }
      end = rdtsc();

      total = (end - strt) / iterations;
      results[expNo] = total;
      aggregate += total;

      /* Print this output entry */
      printEntry(expNo, total);
   }

   /* Print average and stdev */
   stats(results, experiments, &avg, &std);
   printStats(aggregate / (uint64_t)aggregate / expNo, std);
}
