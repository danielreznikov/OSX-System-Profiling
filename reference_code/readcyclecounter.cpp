				std::uint64_t cycles( 0 );
            /** begin assembly section to init previous **/
#ifdef   __x86_64
            __asm__ volatile(
#if RDTSCP  
             "\
               rdtscp                           \n\
               shl      $32, %%rdx              \n\
               orq      %%rax, %%rdx            \n\
               movq     %%rdx, %[cyc]"
#elif defined INTEL
             "\
               lfence                           \n\
               rdtsc                            \n\
               shl      $32, %%rdx              \n\
               orq      %%rax, %%rdx            \n\
               movq     %%rdx, %[cyc]"
#elif defined AMD
             "\
               mfence                           \n\
               rdtsc                            \n\
               shl      $32, %%rdx              \n\
               orq      %%rax, %%rdx            \n\
               movq     %%rdx, %[cyc]"
#elif NOSERIAL
             "\
               rdtsc                            \n\
               shl      $32, %%rdx              \n\
               orq      %%rax, %%rdx            \n\
               movq     %%rdx, %[cyc]"
#endif
               :
               /*outputs here*/
               [cyc]    "=r" (cycles)
               :
               /*inputs here*/
               :
               /*clobbered registers*/
               "rax","eax","rcx","ecx","rdx"
            );
