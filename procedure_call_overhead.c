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
#include<string.h>
#include <inttypes.h>
#include "measuretime.c"
#include "utils.c"


void procedure_call_n_args(int n, ...) {
    return;
}

void procedure_call_zero_args() {
    return;
}

// Run all experiments for a particular procedure
void run_experiments(nparams) {
    int EXPERIMENTS = 10;
    int TRIALS = 1000000;
    
    int expNo;
    uint64_t strt, end;
    float experiment_total;
    float experiment_results [8][EXPERIMENTS];

    // Run experiment
    for (expNo=0; expNo < EXPERIMENTS; ++expNo) {
        experiment_total = 0;

        for (int i = 0; i < TRIALS; ++i) {
            
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
            experiment_total += (end - strt);
        }
        // Save experiment results
        experiment_results[nparams][expNo] = experiment_total / TRIALS;
    }

    // Write results to file
    write_results_matrix_procedure_call_overhead_exp("data/procedure_call_overhead.csv", experiment_results);

    return;
}


// Run all experiments for all procedures
void run() {
    run_experiments(0);
    run_experiments(1);
    run_experiments(2);
    run_experiments(3);
    run_experiments(4);
    run_experiments(5);
    run_experiments(6);
    run_experiments(7);
}


int main() {
    printf("================================");
    printf("\nProcedure Call Overhead Experiments.\n");
    run();
    return 0;
}