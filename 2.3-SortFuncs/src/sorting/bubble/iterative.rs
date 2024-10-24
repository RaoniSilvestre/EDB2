use crate::sorting::OrderedCopy;

pub fn iterative_bubble_sort<T: OrderedCopy>(array: &mut Vec<T>) {
    let len = array.len();
    let mut is_ordered = true;

    for i in 0..len {
        for j in 0..len - 1 - i {
            if array[j] > array[j + 1] {
                is_ordered = false;
                array.swap(j, j + 1)
            }
        }

        if is_ordered {
            break;
        }
    }
}
