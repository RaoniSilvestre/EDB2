use crate::sorting::OrderedCopy;

pub fn recursive_bubble_sort<T: OrderedCopy>(array: &mut Vec<T>) {
    let len = array.len();
    recursive_bubble(array, len)
}

fn recursive_bubble<T: OrderedCopy>(vec: &mut Vec<T>, n: usize) {
    if n == 1 {
        return;
    }
    bubble_pass(vec, 0, n);
    recursive_bubble(vec, n - 1);
}

fn bubble_pass<T: OrderedCopy>(vec: &mut Vec<T>, i: usize, j: usize) {
    if i == j - 1 {
        return;
    }

    if vec[i] > vec[i + 1] {
        vec.swap(i, i + 1);
    }

    bubble_pass(vec, i + 1, j);
}
