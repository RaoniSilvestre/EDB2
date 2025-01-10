#include <stdio.h>
#include <stdlib.h>
#include "arvore_rn.h"

int main() {
    int tamanho = 10;
    int chaves[] = {1, 2, 3, 4, 6, 7, 8, 9, 10, 11};

    raiz = lista_p_arvore(chaves, tamanho);

    printf("Travessia em ordem da árvore criada:\n");
    inorder(raiz);
    printf("\n\n");
    imprimir_arvore(raiz);

    raiz = desalocar(raiz);
    return 0;
}