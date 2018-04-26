/*
 * Final Project | CSE 221 | Spring 2018 | UCSD
 *
 * Header file for utils.c. Implements inline reading from rdtsc.
 */
#ifndef UTILS_H
#define UTILS_H

#include <inttypes.h>
#include <math.h>
#include <stdio.h>

/* Constants */
#define ERR         -1
#define READ        0
#define WRITE       1

/* Define a barrier */
#define B __asm__ __volatile__("" ::: "memory")

/* Reading the cycle ticks */
static inline uint64_t rdtsc() {
	uint32_t eax = 0, edx;

	__asm__ __volatile__("cpuid;" "rdtsc;" : "+a" (eax), "=d" (edx) : : "%rcx", "%rbx", "memory");
	__asm__ __volatile__("xorl %%eax, %%eax;" "cpuid;" : : : "%rax", "%rbx", "%rcx", "%rdx", "memory");

	return (((uint64_t)edx << 32) | eax);
}

/* Printing functions */
void printHeader(char *title);
void printEntry(int experimentNumber, uint64_t entry);
void printStats(double average, double std);

/* Calculating statistics */
void stats(double data[], size_t numElems, double *avg, double *std);

/* 4.1.2 utility calls */
void write_results_matrix_procedure_call_overhead_exp(char filename[100],
    float experiment_results[8][10]);
void write_results_array(char filename[100], float experiment_results[10]);

#endif
