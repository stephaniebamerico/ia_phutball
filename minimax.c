#include "utils.h"
#include "minimax.h"

#include <stdio.h>
#include <stdlib.h>

int heuristica(No *no) {
    // TODO: Heuristica :)
    return 0;
}

int minimax(No *no, int profundidade, bool maximizador) {
  if(no->p_bola == -1 || no->p_bola == no->t_campo || profundidade == 0)
    return heuristica(no);

  if(maximizador) { // esquerda
    // Gera um filho para cada jogada possivel
    // "o": acao de mover a bola
    gera_pulos_direcao(&no, true); // esquerda
    gera_pulos_direcao(&no, false); // direita

    // "f": acao  de inserir um  novo filósofo no campo
    gera_filosofos(&no);

    for (Lista *f = no->filhos; f != NULL; f = f->proximo) {
      printf("Filho: %s\n", f->no->campo);
      printf("Jogada: %s\n", f->no->jogada);
    }
  }

  return 0;
}

/*ROTINA minimax(nó, profundidade, maximizador)
    SE nó é um nó terminal OU profundidade = 0 ENTÃO
        RETORNE o valor da heurística do nó
    SENÃO SE maximizador é FALSE ENTÃO
        α ← +∞
        PARA CADA filho DE nó
            α ← min(α, minimax(filho, profundidade-1,true))
        FIM PARA
        RETORNE α
    SENÃO
        //Maximizador
        α ← -∞
        //Escolher a maior dentre as perdas causadas pelo minimizador
        PARA CADA filho DE nó
            α ← max(α, minimax(filho, profundidade-1,false))
        FIM PARA
        RETORNE α
    FIM SE
FIM ROTINA*/