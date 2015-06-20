LIBS:= -lpthread
CC:= gcc
all: main.out

main.out: main.o lock.o
	${CC} lock.o main.o -o main.out ${LIBS}
main.o: main.c 
	${CC} -c main.c ${LIBS}
lock.o: lock.c
	${CC} -c lock.c ${LIBS}
clean:
	rm *.o main.out
