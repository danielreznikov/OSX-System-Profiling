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


void procedure_call_n_args(int n, ...) {
    return;
}

void procedure_call_zero_args() {
    return;
}

void run_experiment(nparams) {
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
    FILE *fp;
    int i, j;
    char filename[100] = "procedure_call_overhead.data";

    fp=fopen(filename, "w+");
    
    fprintf(fp, "Experiment, Trial_1, Trial_2, Trial_3, Trial_4, Trial_5, Trial_6, Trial_7, Trial_8, Trial_9, Trial_10");
    for(i=0; i<8; i++){
        fprintf(fp,"\n%d",i+1);
        for(j=0; j<EXPERIMENTS; j++)
            fprintf(fp, ",%f ", experiment_results[i][j]);
    }
    fclose(fp);

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