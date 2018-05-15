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
   int status = system("sudo purge");

   printHeader("4.4.1 - File Cache Size");

   // Open data file for reading.
   FILE *fp;
   fp = fopen("data/random16.data", "rb");
   if (fp == NULL) {
      printf("Cannot open file for data input.\n");
      exit(0);
   }

   // Open file for writing results.
   FILE *fpout;
   fpout = fopen("data/file_cache_size_data.out", "w+");
   if (fpout == NULL) {
      printf("Cannot open file for data output.\n");
      exit(0);
   }

   // Compute number of 4KB pages in 16GB file.
   long page_size = 4 * 1024;
   long file_size = 16 * pow(2, 30);
   long num_blocks = file_size / page_size; 

   void *buf = malloc(page_size);
   double *results = (double *)malloc(num_blocks * sizeof(double));

   // Read last byte to buffer the file in main memory.
   if (fseek(fp, 0, SEEK_END) != 0) {
      printf("Cannot seek to end of file.");
      exit(0);
   }
   char first_byte = fgetc(fp);

   // Read a page of data at a time.
   while(1) {
      // Update cursor and read a page.
      fseek(fp, -1*(read_counter+1)*page_size, SEEK_END);
      strt = rdtsc();
      ret_code = fread(buf, page_size, 1, fp);
      end = rdtsc();

      // Read succeeded.
      if (ret_code == 1) {
         bytes += (int)ret_code;
         results[read_counter] = (double)(end - strt);
         printf("Read(%lu) bytes, (%" PRIu64 ") cycles\n",
               page_size*(long)ret_code, end - strt);
         fprintf(fpout, "Read(%lu) bytes, (%" PRIu64 ") cycles\n",
               page_size*(long)ret_code, end - strt);
         read_counter++;
      }
      // Read failed.
      else { 
         if (feof(fp)) {
            printf("Error reading file. Unexpected EOF\n");
            break;  
         }
         else if (ferror(fp)) {
            perror("Error reading file.");
            break;
         }
      }
      
      if (bytes >= file_size)
         break;
   }

   // Cleanup resources.
   fclose(fp);
   fclose(fpout);
   free(buf);
   free(results);
}
