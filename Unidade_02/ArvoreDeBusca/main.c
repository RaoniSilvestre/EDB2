#include <stdio.h>
#include <stdlib.h>
#include "arvore.h"

int main(int argc, char *argv[]) {
    arvore_t *arvre = NULL;
    int chave = 10;

    arvre = inserir(arvre, 30);

    arvre = inserir(arvre, 50);
    arvre = inserir(arvre, 10);

    printf("chave-raiz: %d, achou: %s\n", arvre->chave, buscar(arvre, 2) ? "sim" : "não");
    printf("chave-esq: %d, chave-dir: %d", arvre->esq->chave, arvre->dir->chave);

    desalocar(arvre);

    return EXIT_SUCCESS;
}