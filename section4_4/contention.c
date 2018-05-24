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

/* Spawn contending procs, return averaged measured read time */
unsigned long experiment_iter(int num_processes) {
	pid_t childpids[num_processes];
	uint64_t strt, end, total_time;
	int fds[num_processes][2];
	int bytes_to_read = 4 * pow(2,10); // 4KB

/*
/* Start children. */
for (i = 0; i < n; ++i) {
  if ((pids[i] = fork()) < 0) {
    perror("fork");
    abort();
  } else if (pids[i] == 0) {
    DoWorkInChild();
    exit(0);
  }
}

/* Wait for children to exit. */
int status;
pid_t pid;
while (n > 0) {
  pid = wait(&status);
  printf("Child with PID %ld exited with status 0x%x.\n", (long)pid, status);
  --n;  // TODO(pts): Remove pid from the pids array.
}
*/



	for (int i = 0; i < num_processes; i++) {
		// Generate an 8MB file for this proc to read from.
		exec("./generatedata " i);
		
		// Create a communication channel between parent and child.
		pipe(fds[i]);		

		// Parent is executing.
		if ((childpids[i] = fork()) != 0) {
			close(fds[i][WRITE]);
         
			// Read from empty pipe to force a context switch.
			read(fds[i][READ], &end, sizeof(int));
		}

		// Child is executing.
		else {
			close(fds[i][READ]);

			FILE *fp;
			char fname[11];
			sprintf(fname, "data/proc%d", i); 
			fp = fopen(fname, "rb");

			void *buf = malloc(bytes_to_read);

			strt = rdtsc();
			fread(buf, bytes_to_read, 1, fp);
			end = rdtsc();

			write(fds[i][WRITE], end - strt, sizeof(uint64_t));
			exit(1);
		}
	}
	
	// Aggregate results.

}

/* Driver for Contention experiment */
void measure_read_contention() {
	int num_processes;
	int contention_list[] = {1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024};
	int num_experiments = sizeof(contention_list) / sizeof(int);
	unsigned long results[num_experiments];
	unsigned long res;

	printHeader("4.4.4 - Contention Read Time");

	for (int i = 0; i < num_experiments; i++) {
		num_processes = contention_list[i];
		res = experiment_iter(num_processes);
		results[i] = res;		
		printf("Contentding Procs(%d), Read Time(%lu)", num_processes, res);
	}
}


