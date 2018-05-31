/*
 * Final Project | CSE 221 | Spring 2018 | UCSD
 * 
 * Authors - Daniel Reznikov, Aaron Trefler, Rebecca McKinley
 * 
 * Section 4.4.4 - Contention: Report the average time to read one file system block of 
 *                 data as a function of the number of processes simultaneously performing 
 * 					 the same operation on different files on the same disk (and not in the 
 * 					 file buffer cache).
 */

#include "../utils.h"
#include "driver_4.h"

/* Child process entry point, returns time to read. */
unsigned long runChildProcess(int proc_num) {
	int bytes_to_read = 4 * pow(2,10); // 4KB
   int blocks_to_read = 128; // 128 4KB blocks in a 512KB file.
   int offset = 0;
   uint64_t strt, end, total = 0;
   
   //int locatations[128];
   //for (int i = 0; i < 128; i++) {
   //   locations[i]
   //}

   // Purge the OS file cache.
   system("sudo purge");

   FILE *fp;
   char fname[100] = {0};
   sprintf(fname, "data/data_proc%d", proc_num); 
   fp = fopen(fname, "r");
   if (fp == NULL){
      printf("DEBUG: fp is null, errorno(%s)\n", strerror(errno));
   }

   // Disable file caching.
   if (fcntl(fileno(fp), F_NOCACHE, 1) == -1)
      printf("FAILED to disable cache.\n");

   void *buf = malloc(bytes_to_read);

   for (int i = blocks_to_read; i > 0; i--) {
      offset = -1 * i * bytes_to_read;
      fseek(fp, offset, SEEK_END);

      strt = rdtsc();
      int status = fread(buf, bytes_to_read, 1, fp);
      end = rdtsc();

      if (status == 0)
         printf("DEBUG: fread returned 0, i(%d)\n", i);

      total += (end - strt);
   }


   fclose(fp);
   free(buf);

   return (unsigned long)(total / blocks_to_read);
}

/* Spawn contending procs, return averaged measured read time */
unsigned long experiment_iter(int num_processes) {
	pid_t childpids[num_processes];
	unsigned long results[num_processes];
   unsigned long avg, std, res;
	int fds[num_processes][2];

	for (int i = 0; i < num_processes; i++) {
		// Generate an 512KB file for this proc to read from.
      char gen_data_script[100] = {0};
      sprintf(gen_data_script, "sh generate_data.sh %d &>/dev/null", i); 
		system(gen_data_script);

		// Create a communication channel between parent and child.
		pipe(fds[i]);		

		if ((childpids[i] = fork()) < 0) {
         perror("fork");
         //abort();
         exit(-1);
      }
      else if (childpids[i] == 0) {
         close(fds[i][READ]);
         res = runChildProcess(i);
         write(fds[i][WRITE], &res, sizeof(res));
         close(fds[i][WRITE]);
         exit(0);
      }

      close(fds[i][WRITE]);
   }

   // Wait for children to exit. 
   int idx, status = 0;
   int running_children = num_processes;
   pid_t pid;
   for (idx = 0; idx < num_processes; idx++) {
      pid = wait(&status);
      if (pid < 0)
         perror("wait");
      printf("Child with PID %ld exited with status 0x%x.\n", (long)pid, status);
   }

   // Parent reads data from children pipes.
   for (int j = 0; j < num_processes; j++) {
	   read(fds[j][READ], &(results[j]), sizeof(unsigned long));
      close(fds[j][READ]);
      printf("DEBUG: results[%d] = %lu\n", j, results[j]);
   }
   
	// Aggregate results.
   stats_long(results, 1, &avg, &std);
   int max = 0;
   for (int i=0; i<num_processes; i++) {
      if (results[i] > max)
         max = results[i];
   }

   // Cleanup files.
	for (int i = 0; i < num_processes; i++) {
      char fname[100] = {0};
      sprintf(fname, "data/data_proc%d", i); 
      remove(fname);
   }

   return max;
}

/* Driver for Contention experiment */
void measure_read_contention() {
	int num_processes;
	int contention_list[] = {1, 2, 4, 8, 16, 32, 64};//TODO , 128, 256, 512, 1024};
	int num_experiments = sizeof(contention_list) / sizeof(int);
	unsigned long results[num_experiments];
	unsigned long res;

	printHeader("4.4.4 - Contention Read Time");

	for (int i = 0; i < num_experiments; i++) {
		num_processes = contention_list[i];
      printf("\n");  
		res = experiment_iter(num_processes);
		results[i] = res;		
		printf("Contending Procs(%d), Read Time(%lu)\n", num_processes, res);
	}
}


