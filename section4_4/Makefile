CC=gcc
CLANG=clang
FLAGS=-lpthread -lm -g
4_4_1=file_cache_size.c
4_4_4=contention.c
UTILS=../utils.c

run: *.c
	$(CC) -o 4_driver.out driver_4.c $(4_4_1) $(4_4_2) $(4_4_3) $(4_4_4) pthread_barrier.c $(UTILS) $(FLAGS)

clang: *.c
	$(CLANG) -o 4_driver.out driver_4.c $(4_4_1) $(4_4_2) $(4_4_3) $(4_4_4) $(UTILS) $(FLAGS)

clean:
	rm -rf *.o *.out

new:
	make clean
	make
