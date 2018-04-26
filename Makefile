CC=gcc
CLANG=clang
FLAGS=-lpthread

run: *.c
	$(CC) -o 1_driver.out 1_driver.c $(FLAGS)

clang: *.c
	$(CLANG) -o 1_driver.out 1_driver.c $(FLAGS)

clean:
	rm -rf *.o *.out

new:
	make clean
	make
