CC=gcc
CLANG=clang
FLAGS=-lpthread -lm
4_1_1=measurement_overhead.c
4_1_2=procedure_call_overhead.c
4_1_3=systemcall_overhead.c
4_1_4=process_thread_creation.c
4_1_5=context_switch.c

run: *.c
	$(CC) -o 1_driver.out driver_1.c $(4_1_1) $(4_1_2) $(4_1_3) $(4_1_4) $(4_1_5) utils.c $(FLAGS)

clang: *.c
	$(CLANG) -o 1_driver.out driver_1.c $(4_1_1) $(4_1_2) $(4_1_3) $(4_1_4) $(4_1_5) utils.c $(FLAGS)

clean:
	rm -rf *.o *.out

new:
	make clean
	make
