/*
 * Authors: Daniel Reznikov, Aaaron Trefler, Rebecca McKinley
 *
 * Context switch time: Report the time to context switch from one process to another, and from one kernel thread to another. 
 *                      How do they compare? In the past students have found using blocking pipes to be useful for forcing context switches.
 */
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <pthread.h>
#include "measuretime.c"
#include "utils.c"

// Compute cycles to context switch between 2 processes.
uint64_t process_context_switch() {
   uint64_t strt, end;
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

   if (end > strt)
      return (end - strt);
   else
      return (strt - end);
}

// Run Proccess Context Switch Trials
void process_contextswitch_exps(uint64_t total_experiments, uint64_t trials) {
  double results[total_experiments];
  int expNo;
  uint64_t res;
  double avg, std;
   
  printHeader("4.5 - Process Context Switch Overhead");

  for (expNo=0; expNo<total_experiments; expNo++) {

     res = 0;
     for(int i=0; i<trials; i++) 
        res += process_context_switch();
     
     res /= trials;
     results[expNo] = (double)res;
     printEntry(expNo, res);
  }

  stats(results, total_experiments, &avg, &std);
  printStats(avg, std);
}

// Entry point for new pthread
void * thread_entry(void *param) {
   uint64_t time = rdtsc();
   int fd = (int)param;
   write(fd, &time, sizeof(uint64_t));
   pthread_exit(NULL);
}

// Compute cycles to context switch between 2 threads
uint64_t thread_context_switch() {
   int fd[2];
   pipe(fd);

   uint64_t strt, end, total;

   pthread_t thread1;
   pthread_create(&thread1, NULL, thread_entry, (void*)(uintptr_t)(fd[1]));
   pthread_join(thread1, NULL);
   
   end = rdtsc();
   read(fd[0], &strt, sizeof(uint64_t));

   if (end > strt)
      return (end - strt);
   else
      return (strt - end);
}

// Run Thread Context Switch Experiments
void thread_contextswitch_exps(int total_experiments, int trials) {
   int expNo;
   uint64_t res;
   double results[total_experiments];
   double avg, std;

   printHeader("4.5 - Thread Context Switch Overhead");

   for(expNo=0; expNo<total_experiments; expNo++) {

      res = 0;
      for (int i=0; i<trials; i++) 
         res += thread_context_switch();
      
      res /= trials;
      results[expNo] = (double)res;
      printEntry(expNo, res);
   }

   stats(results, total_experiments, &avg, &std);
   printStats(avg, std);
}

