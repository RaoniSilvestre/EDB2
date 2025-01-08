#include <stdio.h>
#include <stdlib.h>

#include "arvore.h"

int main(int argc, char *argv[]) {
  arvore_t *arvre = NULL;
  int chaves[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  int tamanho = sizeof(chaves) / sizeof(chaves[0]);
  char arquivo[50];

  arvre = lista_p_arvore(chaves, tamanho);
  sprintf(arquivo, "../outputDOT/arvore_de_busca%d.dot", 0);

  printf("\nExportando a árvore para um arquivo DOT...\n");
  exportar_para_dot(arvre, arquivo);
  printf("Arquivo gerado em '%s'\n", arquivo);

  printf("Em ordem:\n");
  mostrarEmOrdem(arvre);
  printf("\nEm pre ordem:\n");
  mostrarPreOrdem(arvre);
  printf("\nEm pos ordem:\n");
  mostrarPosOrdem(arvre);
  printf("\n");

  arvre = desalocar(arvre);

  return EXIT_SUCCESS;
}
