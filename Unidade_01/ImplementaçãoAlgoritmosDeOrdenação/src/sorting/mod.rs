pub mod bubble;
pub mod heap;
pub mod merge;
pub mod quick;

pub use bubble::iterative::iterative_bubble_sort;
pub use bubble::recursive::recursive_bubble_sort;

pub use merge::iterative::iterative_merge_sort;
pub use merge::recursive::recursive_merge_sort;

pub use quick::iterative::iterative_quick_sort;
pub use quick::recursive::recursive_quick_sort;

pub use heap::max_heap::max_heap_sort;
pub use heap::min_heap::min_heap_sort;

pub trait OrderedCopy: PartialOrd + Copy {}

impl<T: PartialOrd + Copy> OrderedCopy for T {}
