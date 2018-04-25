CC=gcc
CLANG=clang
FLAGS=-lpthread

run: *.c
	$(CC) -o driver.out driver.c $(FLAGS)

clang: *.c
	$(CLANG) -o driver.out driver.c $(FLAGS)

clean:
	rm -rf *.o *.out

new:
	make clean
	make
