use heap::MaxHeap;

use crate::sorting::OrderedCopy;

pub fn max_heap_sort<T: OrderedCopy + Default>(array: &mut Vec<T>) {
    let heap: MaxHeap<T> = MaxHeap::from(std::mem::take(array));
    *array = MaxHeap::heapsort(heap);
}
