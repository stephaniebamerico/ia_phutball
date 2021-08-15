#include "utils.h"
#include "minimax.h"

#include <stdio.h>
#include <stdlib.h>

// Estima a quantidade de jogadas para determinado jogador fazer gol
int heuristica(No *no, bool esquerda) { 
  // Se a bola está na frente do gol: "o.." "of." "..o" ".fo" "ffo" "..."  
  if ((esquerda && no->p_bola == no->t_campo-1) ||
        (!esquerda && no->p_bola == 0)) {
    return 5;
  }

  int direcao = esquerda ? 1 : -1;
  int heuristica = 0;
  int n_vazios;
  

  // Se nao existe um filosofo adjacente a bola na direcao do gol
  if (no->campo[no->p_bola+direcao] == VAZIO) 
    ++heuristica;
  
  // Se nao tem um filosofo na borda do gol
  if ((esquerda && no->campo[no->t_campo-1] == VAZIO) ||
        (!esquerda && no->campo[0] == VAZIO))
      ++heuristica;
  
  // Conta quantos filosofos precisariam ser adicionados para fazer o gol 
  // com apenas um pulo: a cada dois vazios seguidos, adicionaria um filosofo
  int i = esquerda ? no->p_bola + 2 : 1;
  int f = esquerda ? no->t_campo - 2 : no->p_bola - 2;
  n_vazios = 0;
  for (; i <= f; ++i) {
    if (no->campo[i] == VAZIO)
      ++n_vazios;
    else
      n_vazios = 0;

    if (n_vazios > 1) {
      ++heuristica;
      n_vazios = 0;
    }
  }

  ++heuristica;
  return heuristica;
}

// Estima a diferenca entre a quantidade de jogadas que cada jogador
// precisa ate fazer gol; quanto maior, melhor para esquerda (e vice-versa)
int calcula_heuristica(No *no) {
  if (no->p_bola == -1) // gol da direita ou esquerda
    return MINIMO;
  if (no->p_bola == no->t_campo) // gol da esquerda
    return MAXIMO;
  // H = R - L
  return heuristica(no, false) - heuristica(no, true);
}

// Minimax ja montando a string da jogada para cada estado calculado
int minimax(No *no, int profundidade, bool maximizador) {
  if(no->p_bola == -1 || no->p_bola == no->t_campo || profundidade == 0)
    return calcula_heuristica(no);
    
  // Gera um filho para cada jogada possivel
  // "o": acao de mover a bola
  gera_pulos_direcao(&no, maximizador, true); // pulos para esquerda
  gera_pulos_direcao(&no, maximizador, false); // pulos para direita
  // "f": acao  de inserir um  novo filósofo no campo
  gera_filosofos(&no, maximizador);
  
  if(maximizador) { // maximizador = esquerda
    // Escolher a maior dentre jogadas do minimizador
    int maximo = MINIMO-1;
    for (Lista *f = no->filhos; f != NULL; f = f->proximo) {
      f->no->h_valor = minimax(f->no, profundidade-1, !maximizador);
      maximo = max(maximo, f->no->h_valor);

      //if(maximo == MAXIMO) // poda: achou melhor caso, nao precisa mais procurar
      //  return maximo;
    }
    return maximo;
  }
  else { // minimizador = direita
    // Escolher a menor dentre jogadas do maximizador
    int minimo = MAXIMO+1;
    for (Lista *f = no->filhos; f != NULL; f = f->proximo) {
      f->no->h_valor = minimax(f->no, profundidade-1, !maximizador);
      minimo = min(minimo, f->no->h_valor);

      //if(minimo == MINIMO) // poda: achou melhor caso, nao precisa mais procurar
      //  return minimo;
    }
    return minimo;
  }
}

// Retorna profundidade maxima para tam_campo
int profundidade_maxima(int tam_campo) {
  if(tam_campo <= 7)
    return 10;
  if(tam_campo <= 9)
    return 8;
  if(tam_campo <= 11)
    return 7;
  if(tam_campo <= 15)
    return 6;
  if(tam_campo <= 21)
    return 5;
  if(tam_campo <= 39)
    return 4;
  if(tam_campo <= 99)
    return 3;
  return 1;
}