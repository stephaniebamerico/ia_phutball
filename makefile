CFLAGS = -g -Wall -Wno-unused-result -O3
LDLIBS = -l hiredis -l readline

all: controlador exemplo1 exemplo2 jogador

controlador: controlador.c

exemplo1: campo.h campo.c exemplo1.c

exemplo2: campo.h campo.c exemplo2.c

jogador: campo.h campo.c utils.h utils.c minimax.h minimax.c jogador.c

clean:
	rm -f controlador exemplo1 exemplo2 jogador *.o
