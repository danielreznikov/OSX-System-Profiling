#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <unistd.h>
#include <math.h>
#include <time.h>
#include <sys/time.h>


// OSX only
#include <mach/mach_time.h>
#include <mach/mach.h>
#include <mach/thread_policy.h>

#define B __asm__ __volatile__("" ::: "memory")

static inline uint64_t
rdtsc(void) {
	uint32_t eax = 0, edx;

	__asm__ __volatile__("cpuid;" "rdtsc;" : "+a" (eax), "=d" (edx) : : "%rcx", "%rbx", "memory");

	__asm__ __volatile__("xorl %%eax, %%eax;" "cpuid;" : : : "%rax", "%rbx", "%rcx", "%rdx", "memory");

	return (((uint64_t)edx << 32) | eax);
}


// Compute standard of deviation of a list of numbers.
float std(float data[], size_t numElems) {

    float sum = 0.0;
    float mean = 0.0;
    float std = 0.0;
    int i = 0;

    for(; i<numElems; ++i) {
        sum += data[i];
    }

    mean = sum/numElems;

    for(i=0; i<numElems; ++i)
        std += pow(data[i] - mean, 2);

    return sqrt(std/numElems);
}

