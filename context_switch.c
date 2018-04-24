/*
 * Authors: Daniel Reznikov, Aaaron Trefler, Rebecca McKinley
 *
 * Context switch time: Report the time to context switch from one process to another, and from one kernel thread to another. 
 *                      How do they compare? In the past students have found using blocking pipes to be useful for forcing context switches.
 */
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include "measuretime.c"
#include "utils.c"

int process_context_switch() {
   uint64_t strt, end, total;
   pid_t childpid;
   
   int fd[2];
   pipe(fd);

   // Parent is executing.
   if ((childpid = fork()) != 0) {
      close(fd[1]);
      strt = rdtsc();

      // Read from empty pipe forces context switch.
      read(fd[0], &end, sizeof(uint64_t));
   }
   
   // Child is executing.
   else {
      end = rdtsc();
      write(fd[1], &end, sizeof(uint64_t));
      exit(1);
   }

   total = end - strt;
   return total > 0 ? (int)total : (int)-total;
}

int proc_contextswitch_exps(int total_experiments) {
  float results[total_experiments];
  int expNo, res;
  float avg, std;

  for (expNo=0; expNo<total_experiments; expNo++) {
      res = process_context_switch();
      results[expNo] = (float)res;
      printf("\nexpNo(%d) context_switch(%d cylces)\n", expNo, res);
  }

  stats(results, total_experiments, &avg, &std)
  printf("avg(%f), std_err(%f)", avg, std);
}
