/*
 * Final Project | CSE 221 | Spring 2018 | UCSD
 *
 * 4.4.2 - Measure and compre file read time using both sequential and random access.
 */
#include "../utils.h"
#include "driver_4.h"
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>


void _print_time_metrics(char *access_type, char *data_file, FILE *output_file, float processor_speed, int total_time) {
    fprintf(output_file, "%s", access_type);
    fprintf(output_file, " , %s", data_file);
    fprintf(output_file, " , Total cycles, %d", total_time);
    fprintf(output_file, " , Total micro seconds, %f \n", (float)total_time / processor_speed * 0.001);
}

void run_random_access(char *data_file, int fd, FILE *fptr, int pages, int page_sz, 
                    FILE *output_file, float processor_speed) {
    char ch;
    int end_time, i, offset, start_time, total_time;

    int random_page [pages];

    printf("\n =====Random Access===== \n");
    printf("File: %s \n", data_file);

    // Turn off data caching
    fcntl(fd, F_NOCACHE, 1);

    // Generate random numbers
    for (i = 0; i < pages; i++) {
        random_page[i] = rand() % pages;
    }

    // Read file using random access
    for (i = 0; i < pages; i++) {
        system("sudo purge");
        start_time = rdtsc();
        ch = fgetc(fptr);
        end_time = rdtsc();

        printf("Character read: '%c'", ch);
        total_time = end_time - start_time;
        _print_time_metrics("random", data_file, output_file, processor_speed, total_time); 
        fseek(fptr, random_page[i] * page_sz, 1);  // set offset to next random page
    }
}


void run_sequential_access(char *data_file, int fd, FILE *fptr, int pages, int page_sz,
                           FILE *output_file, float processor_speed) {
    char ch;
    int end_time, i, start_time, total_time;

    printf("\n =====Sequential Access===== \n");
    printf("File: %s \n", data_file);

    // Turn off data caching
    fcntl(fd, F_NOCACHE, 1);

    // Read file using sequential access
    for (i = 0; i < pages; i++) {
       system("sudo purge");
       start_time = rdtsc();
       ch = fgetc(fptr);
       end_time = rdtsc();

       printf("Character read: '%c'", ch);
       total_time = end_time - start_time;
        _print_time_metrics("sequential", data_file, output_file, processor_speed, total_time);

       fseek(fptr, page_sz, 2);  // increment by 4KB page size
    }
    fclose(fptr);
}


void run_experiment() {
    float PROCESSOR_SPEED = 2.5; // 2.5GHz
    int NUM_FILES = 5;
    int PAGE_SZ = 4096;  // 4KB

    FILE *fptr, *results;
    int fd;

    char *data_file[5] = {  // manually set to NUM_FILES valus
        "/Volumes/Daniel Reznikov's Public Folder/data_4_3/random_16K.data",
        "/Volumes/Daniel Reznikov's Public Folder/data_4_3/random_32K.data",
        "/Volumes/Daniel Reznikov's Public Folder/data_4_3/random_64K.data",
        "/Volumes/Daniel Reznikov's Public Folder/data_4_3/random_128K.data",
        "/Volumes/Daniel Reznikov's Public Folder/data_4_3/random_1256K.data"};
    int pages_in_file[5] = {  // manually set to NUM_FILES valus
          16 * 1024 / PAGE_SZ,
          32 * 1024 / PAGE_SZ,
          64 * 1024 / PAGE_SZ,
         128 * 1024 / PAGE_SZ,
         256 * 1024 / PAGE_SZ};

    results = fopen("results/file_read_time.csv", "w");
    //Run read access experiments
    for (int i = 0; i < NUM_FILES; i++) {
        fptr = fopen(data_file[i], "r");
        fd = fileno(fptr);
        run_sequential_access(data_file[i], fd, fptr, pages_in_file[i], PAGE_SZ, results, PROCESSOR_SPEED);
        close(fd);
    }
    for (int i = 0; i < NUM_FILES; i++) {
        fptr = fopen(data_file[i], "r");
        fd = fileno(fptr);
        run_random_access(data_file[i], fd, fptr, pages_in_file[i], PAGE_SZ, results, PROCESSOR_SPEED);
        close(fd);
    }
    fclose(results);
}


int main() {
    run_experiment();
    return 0;
}
