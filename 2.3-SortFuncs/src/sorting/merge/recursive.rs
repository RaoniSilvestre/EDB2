use crate::sorting::OrderedCopy;

pub fn recursive_merge_sort(array: &mut Vec<impl OrderedCopy>) {
    *array = merge_sorting(array);
}

fn merge_sorting<T: OrderedCopy>(arr: &mut Vec<T>) -> Vec<T> {
    if arr.len() <= 1 {
        return arr.to_vec();
    }
    let mid = arr.len() / 2;
    let left_arr = &arr[0..mid];
    let right_arr = &arr[mid..];
    let left = merge_sorting(&mut left_arr.to_vec());
    let right = merge_sorting(&mut right_arr.to_vec());

    merge(left, right)
}

fn merge<T: OrderedCopy>(arr_1: Vec<T>, arr_2: Vec<T>) -> Vec<T> {
    let mut i = 0;
    let mut j = 0;

    let mut result = Vec::new();

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
