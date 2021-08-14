#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "utils.h"

#define max(a,b) \
({ __typeof__ (a) _a = (a); \
    __typeof__ (b) _b = (b); \
    _a > _b ? _a : _b; })

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

void copia_no(No **novo_no, No *no) {
  (*novo_no) = (No *) malloc(sizeof(No));
  (*novo_no)->campo = (char *) malloc(sizeof(char)*MAXSTR);
  (*novo_no)->campo = strcpy((*novo_no)->campo, no->campo);
  (*novo_no)->t_campo = no->t_campo;
  (*novo_no)->p_bola = no->p_bola;

  (*novo_no)->jogada = (char *) malloc(sizeof(char)*MAXSTR);
  (*novo_no)->filhos = NULL;
}

void insereFilho(Lista **filhos, No *filho) {
    Lista *i;
    if((*filhos) == NULL) {
	    (*filhos) = (Lista *) malloc(sizeof(Lista));
        i = (*filhos);
    }
    else {
        i = (*filhos);
        while (i->proximo != NULL)
            i = i->proximo;

        i->proximo = (Lista *) malloc(sizeof(Lista));
        i = i->proximo;        
    }

    i->no = filho;
    i->proximo = NULL;
}

int heuristica(No *no) {
    // TODO: Heuristica :)
    return 0;
}

// Faz um pulo por vez
void pula(No *no, bool esquerda) {
  // esquerda olha para a direta (+1)
  // direita olha para a esquerda (-1)
  int sinal = esquerda ? 1 : -1;
  // posicao da antiga da bola no campo fica vazia
  no->campo[no->p_bola] = VAZIO;
  int i;
  // vai deixando o campo vazio enquanto pula sobre filosofos
  for(i = 1; no->p_bola+(i*sinal) != -1 && 
            no->p_bola+(i*sinal) != no->t_campo && 
            no->campo[no->p_bola+(i*sinal)] == FILOSOFO; ++i)
    no->campo[no->p_bola+(i*sinal)] = VAZIO;
  // se a bola ainda esta em campo (nao foi gol), coloca ela na nova posicao do campo
  if(no->p_bola+(i*sinal) != -1 && 
            no->p_bola+(i*sinal) != no->t_campo)
    no->campo[no->p_bola+(i*sinal)] = BOLA;
  // atualiza posicao da bola na estrutura do no
  no->p_bola = no->p_bola + (i*sinal);
}

int minimax(No *no, int profundidade, bool maximizador) {
  if(no->p_bola == -1 || no->p_bola == no->t_campo || profundidade == 0)
    return heuristica(no);

  if(maximizador) { // esquerda
    No *novo_no;
    copia_no(&novo_no, no);

    // Gera um filho para cada jogada possivel
    // 1a jogada: pula quantas vezes for possivel
    int n_pulos = 0;
    int *p_pulos = (int *) malloc(sizeof(int)*MAXINT);
    while(novo_no->campo[novo_no->p_bola+1] == FILOSOFO) {
      pula(novo_no, maximizador);      
      p_pulos[n_pulos] = novo_no->p_bola + 1;
      ++n_pulos;
    }
    // Cria a string para jogada de pulos no formato certo
    sprintf(novo_no->jogada, "e o %d", n_pulos);
    for (int i = 0; i < n_pulos; ++i)
      sprintf(novo_no->jogada, "%s %d", novo_no->jogada, p_pulos[i]);
    insereFilho(&(no->filhos), novo_no);

    // 2a jogada: coloca um filosofo

    for (Lista *f = no->filhos; f != NULL; f = f->proximo) {
      printf("Filho: %s\n", f->no->campo);
      printf("Jogada: %s\n", f->no->jogada);
    }      
  }

  return 0;
}