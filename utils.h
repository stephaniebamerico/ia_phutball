#ifndef __UTILS__
#define __UTILS__

#include <stdbool.h>

#define MAXSTR 512
#define MAXINT 16

#define BOLA 'o'
#define FILOSOFO 'f'
#define VAZIO '.'

typedef struct No No;
typedef struct Lista Lista;

// Lista encadeada de nos (estados do campo)
struct Lista {
  No *no;
  
  Lista *proximo;
};

// Estado do campo
struct No {
  // Informacoes sobre o campo
  char *campo; // string do campo
  int t_campo; // tamanho do campo
  int p_bola; // posicao da bola no campo

  // Informacoes para o minimax
  char *jogada; // jogada que levou a esse estado
  int pontuacao; // estimativa da heuristica
  Lista *filhos; // arvore do minimax
};

// Cria uma copia de src em dest (dest = src)
void copia_no(No **dest, No *src);
// Free(no)
void libera_no(No **no);
// Insere um filho (tabuleiro resultante de jogada) na lista de filhos do no
void insere_filho(Lista **filhos, No *filho);

// Pula um grupo de filosofos por vez
void pula(No *no, bool esquerda);
// Gera um estado (filho) para cada pulo possivel em uma direcao
void gera_pulos_direcao(No **no, bool esquerda);
// Gera um estado (filho) para cada filosofo que e possivel colocar em campo
void gera_filosofos(No **no);

#endif