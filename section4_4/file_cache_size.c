/*
 * Final Project | CSE 221 | Spring 2018 | UCSD
 * 
 * Authors - Daniel Reznikov, Aaron Trefler, Rebecca McKinley
 * 
 * Section 4.4.1 - Measure Size of File Cache
 */
#include "../utils.h"
#include "driver_4.h"

void measure_file_cache() {
   uint64_t strt, end;
   ssize_t ret_code, bytes_read = 0;
   int bytes = 0;
   int read_counter = 0;

   // Purge the os file cache.
   // TODO purge(); 

   printHeader("4.4.1 - File Cache Size");

   // Open data file for reading.
   FILE *fp;
   fp = fopen("random16.data", "r");
   if (fp == NULL) {
      printf("Cannot open file for data input.\n");
      exit(0);
   }

   // Open file for writing results.
   FILE *fpout;
   fp = fopen("file_cache_size_data.out", "w+");
   if (fpout == NULL) {
      printf("Cannot open file for data output.\n");
      exit(0);
   }

   // Compute number of 4KB pages in 16GB file.
   long page_size = 4 * 1024;
   long file_size = 16 * pow(2, 30);
   long num_blocks = file_size / page_size; 

   void *buf = malloc(page_size);
   double *results = malloc(num_blocks * sizeof(double));

   // Read one byte to buffer the file in main memory.
   /*if (fseek(fp, 0, SEEK_END) != 0) {
      printf("Cannot seek to end of file.");
      exit(0);
   }*/
   char first_byte = fgetc(fp);

   // Read a page of data at a time.
   while(1) {
      strt = rdtsc();
      ret_code = fread(buf, page_size, 1, fp);
      end = rdtsc();

      // DEBUG TODO REMOVE ME
      printf("ret_code(%d)", (int)ret_code);
      fclose(fp);
      fclose(fpout);
      free(buf);
      free(results);
      exit(0);

      if (ret_code == 1) {
         bytes += (int)ret_code;
         results[read_counter] = (double)(end - strt);
         printf("Read(%d) bytes, (%" PRIu64 ") cycles\n",
               (int)ret_code, end - strt);
         fprintf(fpout, "Read(%d) bytes, (%" PRIu64 ") cycles\n",
               (int)ret_code, end - strt);
         read_counter++;
      }
      else { 
         if (feof(fp)) 
            printf("Error reading file. Unexpected EOF\n");
         else if (ferror(fp))
            perror("Error reading file.");
      }
      
      if (bytes >= file_size)
         break;
   }

   fclose(fp);
   fclose(fpout);
   free(buf);
   free(results);
}
