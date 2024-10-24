use std::{fmt::Display, fs::File, io::Write, path::Path, time::Instant};

use crate::sorting::{
    bubble::{iterative::iterative_bubble_sort, recursive::recursive_bubble_sort},
    merge::recursive::recursive_merge_sort,
    quick::recursive::recursive_quick_sort,
    OrderedCopy,
};

type SortFunction<T> = fn(&mut Vec<T>);

pub fn run<T, F>(mut array: Vec<T>, mut sort_function: F, function_name: String)
where
    T: OrderedCopy + Display,
    F: FnMut(&mut Vec<T>),
{
    let now = Instant::now();
    sort_function(&mut array);
    let elapsed = now.elapsed();

    println!("{}:\n  - TIMING = {:.2?}\n", function_name, elapsed);

    let dir_path = "./data/output/";
    let mut file_name = function_name.clone();
    file_name.push_str(".txt");

    let file_path = Path::new(dir_path).join(file_name.clone());
    let mut file = File::create(file_path).expect("Erro ao criar o arquivo");

    for number in array {
        writeln!(file, "{}", number).expect("Erro ao escrever no arquivo");
    }
}

pub fn run_array(array: Vec<i32>) {
    let array_of_sorts: Vec<(&str, SortFunction<i32>)> = vec![
        ("RECURSIVE_QUICKSORT", recursive_quick_sort),
        ("RECURSIVE_MERGESORT", recursive_merge_sort),
        ("RECURSIVE_BUBBLESORT", recursive_bubble_sort),
        ("ITERATIVE_BUBBLESORT", iterative_bubble_sort),
    ];

    println!("---------------------------\n");
    println!("Array Length: {}\n", array.len());

    for (name, func) in array_of_sorts {
        run::<i32, _>(array.clone(), func, String::from(name));
    }
}
