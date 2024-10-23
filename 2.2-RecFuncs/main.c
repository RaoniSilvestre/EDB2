#include <stdio.h>
#include <time.h>
#include "generator.h"
#include "busca.h"
#include "order.h"

void usage() {

}

void run(uint16_t tamanho, uint8_t chave) {
    uint8_t *vetor = random_generator(tamanho);
    qsort(vetor, tamanho, sizeof(uint8_t), compare);

    int idx_itr, idx_rec;

    clock_t itr_start = clock();
    idx_itr = buscaBinaria(vetor, tamanho, chave);
    clock_t itr_end = clock();

    clock_t rec_start = clock();
    idx_rec = bBinRec(vetor, 0, tamanho - 1, chave);
    clock_t rec_end = clock();

    double cpu_time_used_itr = ((double) (itr_end - itr_start));
    double cpu_time_used_rec = ((double) (rec_end - rec_start));

    printf("--------|%6d|--------\n", tamanho);
    printf("buscaBinaria ; chave: %d => %d ; => %.2lfμs\n", chave, idx_itr, cpu_time_used_itr);
    printf("bBinRec ; chave: %d => %d ; => %.2lfμs\n", chave, idx_rec, cpu_time_used_rec);

    free(vetor);
}

int main(int argc, char *argv[]) {
    if (argc > 2) {
        return 1;
    }

    uint8_t x = (argc == 2 && atoi(argv[1]) != 0 ? atoi(argv[1]): rand() % 100 + 1);

    run(100, x);
    run(1000, x);
    run(10000, x);
    
    return 0;
}
