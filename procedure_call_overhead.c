/*
 * Authors: Daniel, Rebecca, Aaron
 *
 * 4.1.2
 * Procedure Call Overhead
 *
 * Report as a function of number of integer arguments from 0-7.
 * What is the increment overhead of an argument?
 */
#include "utils.h"
#include "driver_1.h"

void procedure_call_n_args(int n, ...) {
    return;
}

void procedure_call_zero_args() {
    return;
}

// Run all experiments for a particular procedure
void run_experiments(int nparams, uint64_t experiments, uint64_t iterations) {
    int expNo;
    uint64_t strt, end;
    float experiment_total;
    float experiment_results [8][experiments];

    // Run experiment
    for (expNo=0; expNo < experiments; ++expNo) {
        experiment_total = 0;

        for (int i = 0; i < iterations; ++i) {

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
        experiment_results[nparams][expNo] = experiment_total / iterations;
    }

    // Write results to file
    write_results_matrix_procedure_call_overhead_exp("data/procedure_call_overhead.csv", experiment_results);

    return;
}


// Run all experiments for all procedures
void run(uint64_t experiments, uint64_t iterations) {
    printHeader("4.1.2 - Procedure Call Overhead (see data/procedure_call_overhead.csv)");
    run_experiments(0, experiments, iterations);
    run_experiments(1, experiments, iterations);
    run_experiments(2, experiments, iterations);
    run_experiments(3, experiments, iterations);
    run_experiments(4, experiments, iterations);
    run_experiments(5, experiments, iterations);
    run_experiments(6, experiments, iterations);
    run_experiments(7, experiments, iterations);
}


// int main() {
//     printf("================================");
//     printf("\nProcedure Call Overhead Experiments.\n");
//     run();
//     return 0;
// }
