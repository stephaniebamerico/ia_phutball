#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "campo.h"

#include "utils.h"
#include "minimax.h"

int main(int argc, char **argv) {
  char buf[MAXSTR];
  No *no = (No *) malloc(sizeof(No));
  no->campo = (char *) malloc(sizeof(char)*MAXSTR);
  no->jogada = NULL;
  no->filhos = NULL;
  char lado_meu;

  // conecta com o controlador do campo
  campo_conecta(argc, argv);

  // recebe o campo inicial e o movimento do adversario
  campo_recebe(buf);

  // separa os elementos do string recebido
  sscanf(strtok(buf, " \n"), "%c", &lado_meu);
  sscanf(strtok(NULL, " \n"), "%d", &(no->t_campo));
  sscanf(strtok(NULL, " \n"), "%s", no->campo);

  // Encontra a posicao da bola no campo
  for(no->p_bola = 0; no->campo[no->p_bola] != BOLA; ++no->p_bola);

  // Encontra a melhor jogada (com minimax)
  No *jogada = melhor_jogada(no, lado_meu); 
  printf("Jogada: %s\n", jogada->jogada);
 
  // envia o movimento para o controlador do campo
  campo_envia(jogada->jogada);
  libera_no(&no);
}
