/* 
 * Authors: Daniel, Rebecca, Aaron
 *
 * 4.1.2 
 * Procedure Call Overhead 
 * 
 * Report as a function of number of integer arguments from 0-7. 
 * What is the increment overhead of an argument?
 */

#include <stdarg.h>
#include <stdio.h>
#include <inttypes.h>
#include "measuretime.c"


void procedure_call_n_args(int n, ...) {
    return;
}

void procedure_call_zero_args() {
    return;
}

void run_experiment(nparams) {
    int EXPERIMENTS = 10;
    int ITERS = 1000000;
    int expNo = 0;
    uint64_t strt, end, total, aggregate = 0;

    // Run experiment
    for (; expNo < 10; ++expNo) {
      strt  = 0;
      end   = 0;
      total = 0;

        for (int i = 0; i < ITERS; ++i) {
            
            switch(nparams) {
            case 0:
                strt = rdtsc();
                procedure_call_zero_args();
                end = rdtsc();
                break;
            case 1:
                strt = rdtsc();
                procedure_call_n_args(0);
                end = rdtsc();
                break;
            case 2:
                strt = rdtsc();
                procedure_call_n_args(1, 0);
                end = rdtsc();
                break;
            case 3:
                strt = rdtsc();
                procedure_call_n_args(2, 0, 0);
                end = rdtsc();
                break;
            case 4:
                strt = rdtsc();
                procedure_call_n_args(3, 0, 0, 0);
                end = rdtsc();
                break;
            case 5:
                strt = rdtsc();
                procedure_call_n_args(4, 0, 0, 0, 0);
                end = rdtsc();
                break;
            case 6:
                strt = rdtsc();
                procedure_call_n_args(5, 0, 0, 0, 0, 0);
                end = rdtsc();
                break;
            case 7:
                strt = rdtsc();
                procedure_call_n_args(6, 0, 0, 0, 0, 0, 0);
                end = rdtsc();
                break;
            }
            total += end - strt;
        }
        // Output experiment results
        total /= ITERS;
        aggregate += total;
    }
    // Output agregate stats
   printf("NParams(%d) Aggregate Stats: Avg(%" PRIu64 ") STD()\n", nparams, aggregate/(uint64_t)expNo);

    return;
}

int main() {
    printf("================================");
    printf("\nProcedure Call Overhead Experiments.\n");
    run_experiment(0);
    run_experiment(1);
    run_experiment(2);
    run_experiment(3);
    run_experiment(4);
    run_experiment(5);
    run_experiment(6);
    run_experiment(7);
    return 0;
}