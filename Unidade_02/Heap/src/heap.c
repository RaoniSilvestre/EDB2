
#include "heap.h"
#include <stdio.h>


void swap(int* H, int i, int j) {
    int temp = H[i];
    H[i] = H[j];
    H[j] = temp;
}

void descer(int* H, int tam, int i) {
  int maior = i;

  if (2*i < tam && H[2*i] < H[maior]) {
    maior = 2 * i; 
  }

  if (2*i + 1 < tam && H[2*i + i] < H[maior]) {
    maior = 2 * i + 1; 
  }
  
  if (maior != i) {
    int temp = H[maior];
    H[maior] = H[i];
    H[i] = temp;
    swap(H, maior, i);

    descer(H, tam, maior);
  }
}


void subir(int *H, int tam, int i) {
  int pai = i/2;
  if (i > 1 && H[i] > H[pai]) {
    swap(H, i, pai);     
    subir(H, tam, pai);
  }
}

void inserir(int *H, int tam,int size, int x) {
  tam += 1;
  if(tam >= size) {
    printf("Impossível adicionar mais valores");
    return;
  }
  H[tam] = x;
  subir(H, size, tam);
}

void remover(int *H, int tam) {
  if(tam > 1) {
    H[1] = H[tam];
    tam -= 1;
    descer(H, tam, 1);
  }
}

