#include "utils.h"
#include "minimax.h"

#include <stdio.h>
#include <stdlib.h>

int heuristica(No *no, bool esquerda) { 
  if (no->p_bola == -1)
    return -1000;
  if (no->p_bola == no->t_campo)
    return 1000; 

  // Se a bola está na frente do gol: "o.." "of." "..o" ".fo" "ffo" "..."  
  if ((esquerda && no->p_bola == no->t_campo-1) ||
        (!esquerda && no->p_bola == 0)) {
    return 5;
  }

  int direcao = esquerda ? 1 : -1;
  int heuristica = 0;
  int n_vazios;
  

  // Verifica se existe um filosofo proximo a bola, na direcao que quer fazer o gol
  if (no->campo[no->p_bola+direcao] == VAZIO) 
    ++heuristica;
  
  // Verifica se tem um "goleiro", i.e. filosofo na borda do gol
  if ((esquerda && no->campo[no->t_campo-1] == VAZIO) ||
        (!esquerda && no->campo[0] == VAZIO))
      ++heuristica;
  
  // Verifica quantos filosofos precisariam ser adicionados para fazer o gol
  int i = esquerda ? no->p_bola + 2 : 1;
  int f = esquerda ? no->t_campo - 2 : no->p_bola - 2;
  printf("i = %d    f = %d\n", i, f);
  n_vazios = 0;
  for (; i <= f; ++i) {
    //printf("Nunca entrou nesse for\n");
    if (no->campo[i] == VAZIO)
      ++n_vazios;
    else
      n_vazios = 0;

    printf("i = %d    n_vazios = %d\n", i, n_vazios);
    if (n_vazios > 1) {
      ++heuristica;
      n_vazios = 0;
    }
  }

  ++heuristica;
  printf("Return heuristica %d\n", heuristica);
  return heuristica;
}

int calcula_heuristica(No *no) {
  return heuristica(no, false) - heuristica(no, true);
}

int minimax(No *no, int profundidade, bool maximizador) {
  printf("\n***\n novo campo %s\n", no->campo);
  printf("Profundidade: %d\n", profundidade);
  if(no->p_bola == -1 || no->p_bola == no->t_campo || profundidade == 0)
    return calcula_heuristica(no);
    
  // Gera um filho para cada jogada possivel
  // "o": acao de mover a bola
  gera_pulos_direcao(&no, true); // esquerda
  gera_pulos_direcao(&no, false); // direita

  // "f": acao  de inserir um  novo filósofo no campo
  gera_filosofos(&no);
  
  if(maximizador) { // esquerda
    int maximo = -10000;
    for (Lista *f = no->filhos; f != NULL; f = f->proximo) {
      maximo = max(maximo, minimax(f->no, profundidade-1, !maximizador));  
    }
    printf("campo: %s  max h: %d\n", no->campo, maximo);
    return maximo;
  }

  else {
    int minimo = 10000;
    for (Lista *f = no->filhos; f != NULL; f = f->proximo) {
      minimo = min(minimo, minimax(f->no, profundidade-1, !maximizador));  
    }
    printf("campo: %s  min h: %d\n", no->campo, minimo);
    return minimo;
  }
  printf("\n");
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