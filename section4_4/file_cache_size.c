/*
 * Final Project | CSE 221 | Spring 2018 | UCSD
 *
 * Authors - Daniel Reznikov, Aaron Trefler, Rebecca McKinley
 *
 * Section 4.4.1 - Measure Size of File Cache
 */
#include "../utils.h"
#include "driver_4.h"

void experiment(double bytes_to_read, int iterations, unsigned long *results) {
   int ret_code;
   uint64_t strt, end;
   long offset, ret = 0;

   // Open data file for reading.
   FILE *fp;
   fp = fopen("data/random16.data", "rb");
   if (fp == NULL) {
      printf("Cannot open file for data input.\n");
      exit(0);
   }

   void *buf = malloc(bytes_to_read);

   // Compute cursor position in file.
   if (bytes_to_read < 16*pow(2,30)) // 16GB
      offset = -1*bytes_to_read -1;
   else
      offset = -1*bytes_to_read;

   // Read to buffer the file in main memory.
   fseek(fp, offset, SEEK_END);
   fread(buf, bytes_to_read, 1, fp);

   for (int i = 0; i < iterations; i++) {
      // Purge the OS file cache.
      int status = system("sudo purge");

      // Read from cursor.
      fseek(fp, offset, SEEK_END);
      strt = rdtsc();
      ret_code = fread(buf, bytes_to_read, 1, fp);
      end = rdtsc();

      // Read succeeded.
      if (ret_code == 1) {
         ret = (unsigned long)(end - strt);
         ret -= READ_TIME_OVERHEAD;
         results[i] = ret;
      }

      // Read failed.
      else {
         if (feof(fp)) {
            printf("Error reading file. Unexpected EOF\n");
            ret = 0;
         }
         else if (ferror(fp)) {
            perror("Error reading file.");
            ret = 0;
         }
      }
   }

   // Cleanup resources.
   fclose(fp);
   free(buf);
}

void measure_file_cache(int iterations) {
   long file_size, read_time;
   unsigned long avg, std;
   unsigned long *results = (unsigned long *)malloc(iterations * sizeof(unsigned long));

   printHeader("4.4.1 - File Cache Size");

   // File Sizes range from 8MB to 15GB.
   long OneMB = pow(1024, 2);
   long OneGB = 1024*OneMB;
   long file_sizes[] = {
      8*OneMB, 16*OneMB, 32*OneMB, 64*OneMB, 128*OneMB, 256*OneMB,
      512*OneMB, OneGB, 2*OneGB, 4*OneGB, 8*OneGB, 11*OneGB, 12*OneGB,
      13*OneGB, 14*OneGB, 15*OneGB
   };

   int num_sizes = sizeof(file_sizes)/sizeof(long);

   // Open file for writing results.
   FILE *fpout;
   fpout = fopen("data/file_cache_size_data.out", "w+");
   if (fpout == NULL) {
      printf("Cannot open file for data output.\n");
      exit(0);
   }

   // Loop over file sizes.
   for (int i = 0; i < num_sizes; i++) {
      file_size = file_sizes[i];

      experiment(file_size, iterations, results);

      stats_long(results, iterations, &avg, &std);

      printf("Read(%lu MB), Mean(%lu cycles), STD(%lu)\n",
            file_size/OneMB, avg, std);
      fprintf(fpout, "Read(%lu MB), Mean(%lu cycles), STD(%lu)\n",
            file_size/OneMB, avg, std);
      fflush(fpout);
   }

   // Cleanup resources.
   fclose(fpout);
   free(results);
}
