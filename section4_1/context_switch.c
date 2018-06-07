/*
 * Final Project | CSE 221 | Spring 2018 | UCSD
 *
 * 4.1.5 - Measure the overhead of a context switch from process to process
 * and from thread to thread.
 */
#include "../utils.h"
#include "driver_1.h"

/* Compute cycles to context switch between 2 processes */
uint64_t process_context_switch() {
   uint64_t strt, end;
   pid_t childpid;
   int fd[2];

   /* Create a communication channel between parent and child */
   pipe(fd);

   /* Parent is executing */
   if ((childpid = fork()) != 0) {
      close(fd[WRITE]);
      strt = rdtsc();

      /* Read from empty pipe and force a context switch */
      read(fd[0], &end, sizeof(uint64_t));
   }

   /* Child is executing */
   else {
      end = rdtsc();
      write(fd[WRITE], &end, sizeof(uint64_t));

      exit(1);
   }

   /* Can't guarantee execution order so take absolute value */
   if (end > strt)
      return (end - strt);
   else
      return (strt - end);
}

/* Run Proccess Context Switch Trials */
void measure_proc_context_switch(uint64_t total_experiments, uint64_t iterations) {
  double results[total_experiments];
  int expNo, i;
  uint64_t res;
  double avg, std;

  printHeader("4.1.5 - Process Context Switch Overhead");

  /* Loop for the given number of experiments */
  for (expNo = 0; expNo < total_experiments; expNo++) {
    res = 0;

    /* Loop a single experiment for given number of iterations */
    for(i = 0; i < iterations; i++)
        res += process_context_switch();

    /* Take average of iterations and update display */
    res /= iterations;
    res -= READ_TIME_OVERHEAD;
    results[expNo] = (double)res;
    printEntry(expNo, res);
  }

  /* Calculate and print the statistics */
  stats(results, total_experiments, &avg, &std);
  printStats(avg, std);
}

/* Entry point for new pthread */
void *thread_entry(void *param) {
   uint64_t time = rdtsc();
   int fd = (int)param;
   write(fd, &time, sizeof(uint64_t));
   pthread_exit(NULL);
}

/* Compute cycles to context switch between 2 threads */
uint64_t thread_context_switch() {
   int fd[2];
   uint64_t strt, end, total;
   pthread_t thread1;

   /* Open up pipe communication between source and spawned thread */
   pipe(fd);

   /* Create and wait on the spawned thread */
   pthread_create(&thread1, NULL, thread_entry, (void*)(uintptr_t)(fd[1]));
   pthread_join(thread1, NULL);

   end = rdtsc();
   read(fd[0], &strt, sizeof(uint64_t));

   /* Can't guarantee execution order so take absolute value */
   if (end > strt)
      return (end - strt);
   else
      return (strt - end);
}

/* Run Thread Context Switch Experiments */
void measure_thread_context_switch(int total_experiments, int iterations) {
   int expNo, i;
   uint64_t res;
   double results[total_experiments];
   double avg, std;

   printHeader("4.1.5 - Thread Context Switch Overhead");

   /* Start the specified number of experiments */
   for(expNo = 0; expNo < total_experiments; expNo++) {
      res = 0;

      /* Run the given number of iterations */
      for (i = 0; i < iterations; i++)
         res += thread_context_switch();

      /* Take average of iterations and update display */
      res /= iterations;
      res -= READ_TIME_OVERHEAD;
      results[expNo] = (double)res;
      printEntry(expNo, res);
   }

   /* Calculate and print statistics */
   stats(results, total_experiments, &avg, &std);
   printStats(avg, std);
}
