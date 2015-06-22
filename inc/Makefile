LIBS:= -lpthread
CC:= gcc
ELF:= inc

all: ${ELF}
${ELF}: ${ELF}.c
	${CC} ${ELF}.c -o ${ELF} ${LIBS}
clean:
	rm  ${ELF}
