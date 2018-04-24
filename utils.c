#ifndef UTILS_C
#define UTILS_C

// Write experiment results to file. Assumes 10 trials per condition
void write_results_matrix_procedure_call_overhead_exp(char filename[100], float experiment_results[8][10]) {

    FILE *fp;
    int i, j;
    char heading[100] = "Experiment, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10";

    fp=fopen(filename, "w+");

    fprintf(fp, "%s", heading);
    for(i=0; i<8; i++){
        fprintf(fp,"\n%d",i+1);
        for(j=0; j<10; j++)
            fprintf(fp, ",%f ", experiment_results[i][j]);
    }
    fprintf(fp, "\n");
    fclose(fp);

    return;
}


// Write experiment results to file. Assumes 10 trials were run.
void write_results_array(char filename[100], float experiment_results[10]) {
    int TRIALS = 10;

    FILE *fp;
    int i, j;
    char heading[100] = "Experiment, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10";

    fp=fopen(filename, "w+");

    fprintf(fp, "%s", heading);
    fprintf(fp,"%d", 0);
    for(i=0; i<TRIALS; i++){
        fprintf(fp, ",%f ", experiment_results[i]);
    }
    fprintf(fp, "\n");
    fclose(fp);

    return;
}
#endif
