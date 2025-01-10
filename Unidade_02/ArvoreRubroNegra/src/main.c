#include <stdio.h>
#include <stdlib.h>
#include "arvore_rn.h"

int main() {
    int n = 10;
    int a[] = {1, 2, 3, 4, 6, 7, 8, 9, 10, 11};

    for (int i = 0; i < n; i++) {
        arvore_rn_t *novo_no = criar_no(a[i]);
        raiz = inserir(raiz, novo_no);
        corrigir_balanceamento(novo_no);
    }

    printf("Travessia em ordem da árvore criada:\n");
    inorder(raiz);
    printf("\n");
    imprimir_arvore(raiz);

    raiz = desalocar(raiz);
    return 0;
}