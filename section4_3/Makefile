CC=gcc
CLANG=clang
FLAGS=-lpthread -lm -g
4_3_1=RAM_access_time.c
4_3_2=RAM_bandwidth.c
4_3_3=page_fault_service.c
UTILS=../utils.c

run: *.py
	python setup_connection.py
#run: *.c
#	$(CC) -o 3_driver.out driver_3.c $(4_3_1) $(4_3_2) $(4_3_3) $(UTILS) $(FLAGS)

#clang: *.c
#	$(CLANG) -o 3_driver.out driver_3.c $(4_3_1) $(4_3_2) $(4_3_3) $(UTILS) $(FLAGS)

clean:
	rm -rf *.o *.out

new:
	make clean
	make
