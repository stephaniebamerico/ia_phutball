#ifndef __MINIMAX__
#define __MINIMAX__

#include "utils.h"

#define MINIMO -10000
#define MAXIMO 10000

#define max(a,b) \
({ __typeof__ (a) _a = (a); \
    __typeof__ (b) _b = (b); \
    _a > _b ? _a : _b; })

#define min(a,b) \
({ __typeof__ (a) _a = (a); \
    __typeof__ (b) _b = (b); \
    _a < _b ? _a : _b; })

// Estima a quantidade de jogadas para determinado jogador fazer gol
int heuristica(No *no, bool esquerda);

// Estima a diferenca entre a quantidade de jogadas que cada jogador
// precisa ate fazer gol; se o gol ja foi feito, retorna um valor limite.
// Quanto maior o valor, melhor para o maximizador (esquerda)
// Quanto menor o valor, melhor para o minimizador (direita)
int calcula_heuristica(No *no);

// Minimax ja montando a string da jogada para cada estado calculado
int minimax(No *no, int profundidade, bool maximizador);

// Retorna profundidade maxima para tam_campo
int profundidade_maxima(int tam_campo);
#endif