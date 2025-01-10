use heap::MinHeap;

use crate::sorting::OrderedCopy;

pub fn min_heap_sort<T: OrderedCopy + Default>(array: &mut Vec<T>) {
    let heap: MinHeap<T> = MinHeap::from(std::mem::take(array));
    *array = MinHeap::heapsort(heap);
}
