#[cfg(test)]
mod tests {
    use rusty_algoritms::{
        generate_list,
        sorting::{
            bubble::iterative::iterative_bubble_sort, merge::recursive::recursive_merge_sort,
            merge::iterative::iterative_merge_sort, quick::recursive::recursive_quick_sort,
        },
    };

    #[test]
    fn it_works() {
        let result = 2 + 2;
        assert_eq!(result, 4);
    }

    #[test]
    fn iterative_bubble_sort_test_10x1000() {
        for _ in 0..10 {
            let mut random_list = generate_list(1000);
            let mut random_list_2 = random_list.clone();
            random_list_2.sort();
            iterative_bubble_sort(&mut random_list);
            assert_eq!(random_list, random_list_2)
        }
    }

    #[test]
    fn recursive_quick_sort_test10x1000() {
        for _ in 0..10 {
            let mut random_list = generate_list(1000);
            let mut random_list_2 = random_list.clone();
            recursive_quick_sort(&mut random_list);
            random_list_2.sort();
            assert_eq!(random_list, random_list_2);
        }
    }

    #[test]
    fn recursive_merge_sort_test10x1000() {
        for _ in 0..10 {
            let mut random_list = generate_list(1000);
            let mut random_list_2 = random_list.clone();
            recursive_merge_sort(&mut random_list);
            random_list_2.sort();
            assert_eq!(random_list, random_list_2);
        }
    }

    #[test]
    fn iterative_merge_sort_test10x1000() {
        for _ in 0..10 {
            let mut random_list = generate_list(1000);
            let mut random_list_2 = random_list.clone();
            iterative_merge_sort(&mut random_list);
            random_list_2.sort();
            assert_eq!(random_list, random_list_2);
        }
    }
}

