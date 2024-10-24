use crate::sorting::OrderedCopy;

pub fn recursive_quick_sort<T: OrderedCopy>(array: &mut Vec<T>) {
    sorting(array, 0, array.len() - 1)
}

fn sorting<T: OrderedCopy>(lista: &mut Vec<T>, left: usize, right: usize) {
    if left < right {
        let index_pivot = partition(lista, left, right);
        sorting(lista, left, index_pivot);
        sorting(lista, index_pivot + 1, right);
    }
}

fn partition<T: OrderedCopy>(lista: &mut Vec<T>, mut left: usize, mut right: usize) -> usize {
    let pivot = left;
    left += 1;
    while left <= right {
        while left < lista.len() && lista[left] < lista[pivot] {
            left += 1;
        }
        while lista[right] > lista[pivot] {
            if right == 0 {
                break;
            }
            right -= 1;
        }
        if right >= left {
            lista.swap(left, right);
            if right != 0 {
                right -= 1;
            }
        }
    }
    lista.swap(pivot, right);
    right
}
