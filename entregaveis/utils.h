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
  int h_valor; // estimativa da heuristica
  Lista *filhos; // arvore do minimax
};

// Usa minimax para determinar melhor jogada
No *melhor_jogada(No *no, char lado);

// Cria uma copia de no src em no dest (dest = src)
void copia_no(No **dest, No *src);
// Free(no) e seus componentes
void libera_no(No **no);
// Insere um filho (campo resultante de jogada) na lista de filhos do no
void insere_filho(Lista **filhos, No *filho);

// Faz um pulo por vez na direcao indicada
void pula(No *no, bool esquerda);
// Gera um estado (filho) para cada pulo possivel em uma direcao
void gera_pulos_direcao(No **no, bool maximizador, bool esquerda);
// Gera um estado (filho) para cada filosofo que e possivel colocar em campo
void gera_filosofos(No **no, bool maximizador);
#endif