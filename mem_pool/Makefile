all:
	gcc -c -g -Wall mem_pool.c
	gcc -g -Wall main.c mem_pool.o -o mm.out -lpthread -lrt
clean:
	rm mm.out mem_pool.o
