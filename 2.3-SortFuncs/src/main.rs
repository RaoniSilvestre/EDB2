use rusty_algoritms::{
    read_numbers_from_file,
    running::*,
    sorting::{
        bubble::{iterative::iterative_bubble_sort, recursive::recursive_bubble_sort},
        merge::recursive::recursive_merge_sort,
        quick::recursive::recursive_quick_sort,
    },
};

fn main() {
    let files = vec![
        "./data/input/file_1000.txt",
        "./data/input/file_10000.txt",
        "./data/input/file_100000.txt",
    ];

    for file in files {
        let array = read_numbers_from_file(file).expect("Não foi possível ler arquivo");
        run_array(array);
    }
}

fn run_array(array: Vec<i32>) {
    println!("---------------------------");
    println!("---------------------------");
    println!("Array Length: {}", array.len());
    println!("=========RECURSIVOS========");
    run::<i32, _>(
        array.clone(),
        recursive_quick_sort,
        String::from("QuickSort_recursivo"),
    );

    run::<i32, _>(
        array.clone(),
        recursive_merge_sort,
        String::from("MergeSort_recursivo"),
    );

    run::<i32, _>(
        array.clone(),
        recursive_bubble_sort,
        String::from("BubbleSort_recursivo"),
    );

    println!("=========ITERATIVOS========");
    run::<i32, _>(
        array,
        iterative_bubble_sort,
        String::from("BubbleSort_iterativo"),
    )
}
