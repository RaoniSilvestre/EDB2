#[cfg(test)]
mod tests {
    use heap::MinHeap;

    #[test]
    fn test_push() {
        let mut heap = MinHeap::default();
        heap.push(5);
        heap.push(3);
        heap.push(8);
        heap.push(1);

        assert_eq!(heap.peek(), Some(&1));
        assert_eq!(heap.len(), 4);
    }

    #[test]
    fn test_pop() {
        let mut heap = MinHeap::default();
        heap.push(5);
        heap.push(3);
        heap.push(8);
        heap.push(1);

        assert_eq!(heap.pop(), Some(1));
        assert_eq!(heap.pop(), Some(3));
        assert_eq!(heap.pop(), Some(5));
        assert_eq!(heap.pop(), Some(8));
        assert!(heap.is_empty());
    }

    #[test]
    fn test_from_vec() {
        let heap: MinHeap<i32> = MinHeap::from(vec![10, 3, 8, 5, 2]);
        assert_eq!(heap.peek(), Some(&2));
        assert_eq!(heap.len(), 5);
    }

    #[test]
    fn test_empty_heap() {
        let mut heap: MinHeap<i32> = MinHeap::default();
        assert!(heap.is_empty());
        assert_eq!(heap.len(), 0);
        assert_eq!(heap.pop(), None);
        assert_eq!(heap.peek(), None);
    }

    #[test]
    fn test_heap_property() {
        let mut heap = MinHeap::default();
        heap.push(20);
        heap.push(15);
        heap.push(30);
        heap.push(10);

        assert_eq!(heap.pop(), Some(10));
        assert_eq!(heap.pop(), Some(15));
        assert_eq!(heap.pop(), Some(20));
        assert_eq!(heap.pop(), Some(30));
    }

    #[test]
    fn test_large_input() {
        let mut heap = MinHeap::default();
        for i in (0..1000).rev() {
            heap.push(i);
        }

        for i in 0..1000 {
            assert_eq!(heap.pop(), Some(i));
        }
    }
}
