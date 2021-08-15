CFLAGS = -g -Wall -Wno-unused-result -O3
LDLIBS = -l hiredis -l readline

all: jogador

jogador: campo.h campo.c utils.h utils.c minimax.h minimax.c jogador.c

clean:
	rm -f jogador *.o
