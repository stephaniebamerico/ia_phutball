#ifndef __MINIMAX__
#define __MINIMAX__

#include "utils.h"

#define max(a,b) \
({ __typeof__ (a) _a = (a); \
    __typeof__ (b) _b = (b); \
    _a > _b ? _a : _b; })

#define min(a,b) \
({ __typeof__ (a) _a = (a); \
    __typeof__ (b) _b = (b); \
    _a < _b ? _a : _b; })

// Estimativa TODO: EXPLICAR
int heuristica(No *no);
// TODO: EXPLICAR
int minimax(No *no, int profundidade, bool maximizador);

#endif