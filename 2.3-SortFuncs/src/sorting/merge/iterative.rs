use crate::sorting::OrderedCopy;

pub fn iterative_merge_sort(array: &mut Vec<impl OrderedCopy>) {
    *array = merge_sorting(array, array.len());
}

fn merge_sorting<T: OrderedCopy>(arr: &Vec<T>, tamanho: usize) -> Vec<T> {
    let mut result: Vec<T> = arr.to_vec();
    let mut i: usize = 1;

    while i < tamanho {
        let mut esquerda: usize = 0;

        while esquerda < tamanho - 1 {
            let mid: usize = std::cmp::min(esquerda + i - 1, tamanho - 1);
            let right_arr: usize = std::cmp::min(esquerda + 2 * i - 1, tamanho - 1);

            
            let merged: Vec<T> = merge(
                &result[esquerda..mid + 1].to_vec(),
                &result[mid + 1..right_arr + 1].to_vec(),
            );


            for k in 0..merged.len() {
                result[esquerda + k] = merged[k].clone();
            }

            esquerda += 2 * i;
        }

        i *= 2;
    }

    result // Retorna o vetor ordenado
}

fn merge<T: OrderedCopy>(arr_1: &Vec<T>, arr_2: &Vec<T>) -> Vec<T> {
    let mut i: usize = 0;
    let mut j: usize = 0;

    let mut result: Vec<T> = Vec::new();

    while i < arr_1.len() && j < arr_2.len() {
        if arr_2[j] > arr_1[i] {
            result.push(arr_1[i]);
            i += 1;
        } else {
            result.push(arr_2[j]);
            j += 1;
        }
    }

    while i < arr_1.len() {
        result.push(arr_1[i]);
        i += 1;
    }

    while j < arr_2.len() {
        result.push(arr_2[j]);
        j += 1;
    }

    result
}