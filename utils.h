#include <stdbool.h>

#define MAXSTR 512
#define MAXINT 16

#define BOLA 'o'
#define FILOSOFO 'f'
#define VAZIO '.'

typedef struct No No;
typedef struct Lista Lista;

struct Lista {
  No *no;
  
  Lista *proximo;
};


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

// Insere um filho (tabuleiro resultante de jogada) na lista de filhos do no
void insereFilho(Lista **filhos, No *filho);
// Estimativa TODO: EXPLICAR
int heuristica(No *no);
// Pula um grupo de filosofos por vez
void pula(No *no, bool esquerda);
// TODO: EXPLICAR
int minimax(No *no, int profundidade, bool maximizador);