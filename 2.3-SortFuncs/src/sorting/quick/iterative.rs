use crate::sorting::OrderedCopy;

pub fn iterative_quick_sort<T: OrderedCopy>(array: &mut Vec<T>) {
    let mut stack = Vec::new();
    let tamanho = array.len();

    stack.push(0);
    stack.push(tamanho - 1);

    while let Some(right) = stack.pop() {
        if let Some(left) = stack.pop() {
            let pivo_index = particionar(array, left, right);

            if pivo_index > 0 && pivo_index - 1 > left {
                stack.push(left);
                stack.push(pivo_index - 1);
            }

            if pivo_index + 1 < right {
                stack.push(pivo_index + 1);
                stack.push(right);
            }
        }
    }
}

fn particionar<T: OrderedCopy>(array: &mut [T], left: usize, rigth: usize) -> usize {
    let pivo = array[rigth];
    let mut i = left as isize - 1;

    for j in left..(rigth) {
        if array[j] <= pivo {
            i += 1;
            array.swap(i as usize, j);
        }
    }

    array.swap((i + 1) as usize, rigth);
    (i + 1) as usize
}
