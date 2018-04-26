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

void procedure_call_seven_args(int one, int two, int three, int four, int five, int six, int seven) {return;}


void procedure_call_six_args(int one, int two, int three, int four, int five, int six) {return;}


void procedure_call_five_args(int one, int two, int three, int four, int five) {return;}


void procedure_call_four_args(int one, int two, int three, int four) {return;}


void procedure_call_three_args(int one, int two, int three) {return;}


void procedure_call_two_args(int one, int two) {return;}


void procedure_call_one_args(int one) {return;}


void procedure_call_zero_args() {return;}


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
                procedure_call_one_args(1);
                end = rdtsc();
                break;
            case 2:
                strt = rdtsc();
                procedure_call_two_args(1, 2);
                end = rdtsc();
                break;
            case 3:
                strt = rdtsc();
                procedure_call_three_args(1, 2, 3);
                end = rdtsc();
                break;
            case 4:
                strt = rdtsc();
                procedure_call_four_args(1, 2, 3, 4);
                end = rdtsc();
                break;
            case 5:
                strt = rdtsc();
                procedure_call_five_args(1, 2, 3, 4, 5);
                end = rdtsc();
                break;
            case 6:
                strt = rdtsc();
                procedure_call_six_args(1, 2, 3, 4, 5, 6);
                end = rdtsc();
                break;
            case 7:
                strt = rdtsc();
                procedure_call_seven_args(1, 2, 3, 4, 5, 6, 7);
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
//     run(10, 10000000);
//     return 0;
// }
