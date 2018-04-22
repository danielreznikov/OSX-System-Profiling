#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <unistd.h>

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
