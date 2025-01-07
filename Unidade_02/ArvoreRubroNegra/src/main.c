#include <stdio.h>
#include "arvore_rn.h"

int main() {
    arvore_rn_t *arvore = NULL;
    int chaves[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int tamanho = sizeof(chaves) / sizeof(chaves[0]);
    //arvore = lista_p_arvore(chaves, tamanho);

    arvore = inserir(arvore, 1);
    arvore = inserir(arvore, 2);
    arvore = inserir(arvore, 3);
    arvore = inserir(arvore, 4);
    arvore = inserir(arvore, 5);
    arvore = inserir(arvore, 6);
    arvore = inserir(arvore, 7);
    arvore = inserir(arvore, 8);
    arvore = inserir(arvore, 9);
    arvore = inserir(arvore, 10);

    imprimir_arvore(arvore);
    //inorder(arvore);
    arvore = desalocar(arvore);

    return 0;
}