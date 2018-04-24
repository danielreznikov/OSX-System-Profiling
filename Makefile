CC=gcc
CLANG=clang

run: *.c
	$(CC) driver.c

clang: *.c
	$(CLANG) driver.c
