#pragma once

#include <stdint.h>
#include <stdlib.h>

/**
 * @brief Realiza uma busca binária de forma iterativa em um vetor de inteiros sem sinal de 8 bits.
 *
 * Esta função procura por uma chave específico em um vetor ordenado de inteiros
 * sem sinal de 8 bits utilizando o algoritmo de busca binária iterativa.
 *
 * @param vetor Ponteiro para o início do vetor de inteiros sem sinal de 8 bits.
 * @param tamanho Tamanho do vetor.
 * @param chave Chave a ser buscado no vetor.
 * @return O índice da chave no vetor, se encontrada. Caso contrário, retorna -1.
 */
int16_t buscaBinaria(uint8_t* vetor, uint16_t tamanho, uint8_t chave) {
    uint16_t esq = 0;
    uint16_t dir = tamanho - 1;
    uint16_t m;

    while (esq < dir) {
        m = (esq + dir) / 2;
        if (chave > vetor[m]) {
            esq = m + 1;
        } else {
            dir = m;
        }
    }

    return vetor[esq] == chave ? esq : -1;
}

/**
 * @brief Realiza uma busca binária recursiva em um vetor de inteiros.
 *
 * Esta função busca uma chave específico em um vetor ordenado de inteiros
 * utilizando o algoritmo de busca binária recursiva.
 *
 * @param vetor Ponteiro para o vetor de inteiros onde a busca será realizada.
 * @param esq Índice inicial (esquerda) do intervalo de busca.
 * @param dir Índice final (direita) do intervalo de busca.
 * @param chave Chave a ser buscado no vetor.
 * @return O índice do chave encontrado no vetor, ou -1 se a chave não for encontrado.
 */
int16_t bBinRec(uint8_t* vetor, uint16_t esq, uint16_t dir, uint8_t chave) {
    if (esq >= dir && vetor[esq] != chave) {
        return -1;
    }
    
    uint16_t m = esq + (dir - esq) / 2;

    if (vetor[m] == chave) {
        return m;
    }

    return vetor[m] > chave ? bBinRec(vetor, esq, m - 1, chave) : bBinRec(vetor, m + 1, dir, chave);
}