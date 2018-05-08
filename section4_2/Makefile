CC=gcc
CLANG=clang
FLAGS=-lpthread -lm
4_1_1=RAM_access_time.c
4_1_2=RAM_bandwidth.c
4_1_3=page_fault_service.c
UTILS=../utils.c

run: *.c
	$(CC) -o 2_driver.out driver_2.c $(4_1_1) $(4_1_2) $(4_1_3) $(UTILS) $(FLAGS)

clang: *.c
	$(CLANG) -o 2_driver.out driver_2.c $(4_1_1) $(4_1_2) $(4_1_3) $(UTILS) $(FLAGS)

clean:
	rm -rf *.o *.out

new:
	make clean
	make
