#include "utils.h"
#include "minimax.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Usa minimax para determinar melhor jogada
No *melhor_jogada(No *no, char lado) {
  // Determina profundidade maxima para o tamanho do campo
  int profundidade = profundidade_maxima(no->t_campo);
  
  No *melhor_jogada = NULL;
  if(lado == 'e') { // Jogador esquerda = maximizador
    // Gera arvore de jogadas com a profundidade determinada
    minimax(no, profundidade, true);

    // Encontra a jogada com o maior valor da heuristica
    // Ou a jogada que resulta em gol imediatamente
    int max = MINIMO-1;
    for (Lista *f = no->filhos; f != NULL; f = f->proximo) {
      if(max < f->no->h_valor || 
        f->no->p_bola == 0 || f->no->p_bola == no->t_campo) {
        melhor_jogada = f->no;
        max = f->no->h_valor;
      }
    }
  }
  else { // Jogador direita = minimizador
    // Gera arvore de jogadas com a profundidade determinada
    minimax(no, profundidade, false);

    // Encontra a jogada com o menor valor da heuristica
    // Ou a jogada que resulta em gol imediatamente
    int min = MAXIMO+1;
    for (Lista *f = no->filhos; f != NULL; f = f->proximo) {
      if(min > f->no->h_valor || 
        f->no->p_bola == 0 || f->no->p_bola == no->t_campo) {
        melhor_jogada = f->no;
        min = f->no->h_valor;
      }
    }
  }
  return melhor_jogada;
}

// Cria uma copia de no src em no dest (dest = src)
void copia_no(No **dest, No *src) {
  (*dest) = (No *) malloc(sizeof(No));
  (*dest)->campo = (char *) malloc(sizeof(char)*MAXSTR);
  (*dest)->campo = strcpy((*dest)->campo, src->campo);
  (*dest)->t_campo = src->t_campo;
  (*dest)->p_bola = src->p_bola;

  (*dest)->jogada = (char *) malloc(sizeof(char)*MAXSTR);
  if(src->jogada != NULL)
    strcpy((*dest)->jogada, src->jogada);
  else
    (*dest)->jogada[0] = '\0';
  (*dest)->filhos = NULL;
}

// Free(no) e seus componentes
void libera_no(No **no) {
  if(*no == NULL)
    return;

  if((*no)->campo != NULL)
    free((*no)->campo);
  if((*no)->jogada != NULL)
    free((*no)->jogada);
  if((*no)->filhos != NULL) {
    Lista *aux = (*no)->filhos;
    while(aux != NULL) {
      libera_no(&(aux->no));
      Lista *t = aux;
      aux = aux->proximo;
      free(t);
    }
  }
  free(*no);
}

// Insere um filho (campo resultante de jogada) na lista de filhos do no
void insere_filho(Lista **filhos, No *filho) {
    Lista *i;
    if((*filhos) == NULL) {
      // Se nao ha filhos na lista, aloca o primeiro
	    (*filhos) = (Lista *) malloc(sizeof(Lista));
        i = (*filhos);
    }
    else {
      // Se ja ha filhos na lista, aloca espaco no fim da lista
      i = (*filhos);
      while (i->proximo != NULL)
          i = i->proximo;

      i->proximo = (Lista *) malloc(sizeof(Lista));
      i = i->proximo;        
    }

    i->no = filho;
    i->proximo = NULL;
}

// Faz um pulo por vez na direcao indicada
void pula(No *no, bool esquerda) {
  // Direta = +1
  // Esquerda = -1
  int sinal = esquerda ? 1 : -1;
  // Posicao da antiga da bola no campo fica vazia
  no->campo[no->p_bola] = VAZIO;
  int i;
  // Vai deixando o campo vazio enquanto pula sobre filosofos
  for(i = 1; no->p_bola+(i*sinal) != -1 && 
            no->p_bola+(i*sinal) != no->t_campo && 
            no->campo[no->p_bola+(i*sinal)] == FILOSOFO; ++i)
    no->campo[no->p_bola+(i*sinal)] = VAZIO;
  // Se a bola ainda esta em campo (nao foi gol), coloca ela na nova posicao do campo
  if(no->p_bola+(i*sinal) != -1 && 
            no->p_bola+(i*sinal) != no->t_campo)
    no->campo[no->p_bola+(i*sinal)] = BOLA;
  // Atualiza posicao da bola na estrutura do no
  no->p_bola = no->p_bola + (i*sinal);
}

// Gera um estado (filho) para cada pulo possivel em uma direcao
void gera_pulos_direcao(No **no, bool maximizador, bool esquerda) {
  int direcao = esquerda ? 1 : -1;

  No *novo_no;
  copia_no(&novo_no, *no);

  // Gera um filho para cada pulo possivel na direcao determinada
  int n_pulos = 0;
  int *p_pulos = (int *) malloc(sizeof(int)*MAXINT);
  while(novo_no->campo[novo_no->p_bola+direcao] == FILOSOFO) {
    pula(novo_no, esquerda);      
    p_pulos[n_pulos] = novo_no->p_bola + 1;
    ++n_pulos;

    // Cria a string para jogada no formato correto
    if (maximizador)
      sprintf(novo_no->jogada, "e");
    else
      sprintf(novo_no->jogada, "d");
    sprintf(novo_no->jogada, "%s o %d", novo_no->jogada, n_pulos);
    for (int i = 0; i < n_pulos; ++i)
      sprintf(novo_no->jogada, "%s %d", novo_no->jogada, p_pulos[i]);
    sprintf(novo_no->jogada, "%s\n", novo_no->jogada);
    No *no_aux;
    copia_no(&no_aux, novo_no);
    insere_filho(&((*no)->filhos), no_aux);
  }
  libera_no(&novo_no);
  free(p_pulos);
}

// Gera um estado (filho) para cada filosofo que e possivel colocar em campo
void gera_filosofos(No **no, bool maximizador) {
  for (int i = 0; i < (*no)->t_campo; i++) {
    // Coloca um filosofo em cada espaco vazio no campo
    if ((*no)->campo[i] == VAZIO) {
        No *novo_no;
        copia_no(&novo_no, *no);
        novo_no->campo[i] = FILOSOFO;
        
        // Cria a string para jogada no formato correto
        if(maximizador)
          sprintf(novo_no->jogada, "e f %d\n", i+1);
        else
          sprintf(novo_no->jogada, "d f %d\n", i+1);
        
        insere_filho(&((*no)->filhos), novo_no);
    }
  }
}