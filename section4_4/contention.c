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
   uint64_t strt, end;

   FILE *fp;
   char fname[11];
   sprintf(fname, "data/proc%d", proc_num); 
   fp = fopen(fname, "rb");

   void *buf = malloc(bytes_to_read);

   strt = rdtsc();
   fread(buf, bytes_to_read, 1, fp);
   end = rdtsc();

   //write(fds[i][WRITE], end - strt, sizeof(uint64_t));
   //exit(1);
   //close(fds[i][WRITE]);
   
   fclose(fp);

   return (unsigned long)(end - strt);
}

/* Spawn contending procs, return averaged measured read time */
unsigned long experiment_iter(int num_processes) {
	pid_t childpids[num_processes];
	unsigned long results[num_processes];
   unsigned long avg, std;
	//int fds[num_processes][2];

	for (int i = 0; i < num_processes; i++) {
		// Generate an 8MB file for this proc to read from.
      char gen_data_script[100] = {0};
      sprintf(gen_data_script, "sh generate_data.sh %d &>/dev/null", i); 
		system(gen_data_script);

		// Create a communication channel between parent and child.
		// pipe(fds[i]);		

		if ((childpids[i] = fork()) < 0) {
         perror("fork");
         abort();
      }
      else if (childpids[i] == 0) {
         results[i] = runChildProcess(i);
         exit(0);
      }
   
      // Wait for children to exit. 
      int status;
      pid_t pid;
      while (num_processes > 0) {
         pid = wait(&status);
         perror("wait");
         printf("Child with PID %ld exited with status 0x%x.\n", (long)pid, status);
         --num_processes; 
      }
   }
   // Read from empty pipe to force a context switch.
	// read(fds[i][READ], &end, sizeof(int));
   
	// Aggregate results.
   stats_long(results, 1, &avg, &std);

   // Cleanup files.
	for (int i = 0; i < num_processes; i++) {
      char fname[100] = {0};
      sprintf(fname, "data/proc%d", i); 
      remove(fname);
   }

   return avg;
}

/* Driver for Contention experiment */
void measure_read_contention() {
	int num_processes;
	int contention_list[] = {1, 2, 4, 8}; // TODO, 16, 32, 64, 128, 256, 512, 1024};
	int num_experiments = sizeof(contention_list) / sizeof(int);
	unsigned long results[num_experiments];
	unsigned long res;

	printHeader("4.4.4 - Contention Read Time");

	for (int i = 0; i < num_experiments; i++) {
		num_processes = contention_list[i];
      printf("\n");  
		res = experiment_iter(num_processes);
		results[i] = res;		
		printf("Contentding Procs(%d), Read Time(%lu)\n", num_processes, res);
	}
}


