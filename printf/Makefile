#LIBS:= -lpthread
CC:= gcc
CFLAGS := -g -static
all: main.out

main.out: main.o 
	${CC} ${CFLAGS} main.o -o main.out ${LIBS}
main.o: main.c 
	${CC} ${CFLAGS} -c main.c ${LIBS}
clean:
	rm *.o main.out
