#include <stdio.h>
#include <stdlib.h>

#include "arvore.h"

int main(int argc, char *argv[]) {
    arvore_t *arvre = NULL;
    int chave = 10;

    arvre = inserir(arvre, 30);

    arvre = inserir(arvre, 50);
    inorder(arvre);
    printf("\n");

    arvre = remover(arvre, 50);
    inorder(arvre);
    printf("\n");
    desalocar(arvre);

    return EXIT_SUCCESS;
}
