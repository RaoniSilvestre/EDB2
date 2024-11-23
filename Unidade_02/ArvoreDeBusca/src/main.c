#include <stdio.h>
#include <stdlib.h>

#include "arvore.h"

int main(int argc, char *argv[]) {
    arvore_t *arvre = NULL;
    int chaves[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int tamanho = sizeof(chaves) / sizeof(chaves[0]);
    
    arvre = lista_p_arvore(chaves, tamanho);

    inorder(arvre);
    printf("\n");
    arvre = desalocar(arvre);

    return EXIT_SUCCESS;
}
