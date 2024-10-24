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

    println!("{} Timing: {:.2?} ", function_name, elapsed,);

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
    let array_of_recursive: Vec<(&str, SortFunction<i32>)> = vec![
        ("QuickSort_recursivo", recursive_quick_sort),
        ("MergeSort_recursivo", recursive_merge_sort),
        ("BubbleSort_recursivo", recursive_bubble_sort),
    ];
    let array_of_iterative: Vec<(&str, SortFunction<i32>)> =
        vec![("BubbleSort_iterativo", iterative_bubble_sort)];

    println!("---------------------------");
    println!("---------------------------");
    println!("Array Length: {}", array.len());
    println!("=========RECURSIVOS========");
    for (name, func) in array_of_recursive {
        run::<i32, _>(array.clone(), func, String::from(name));
    }

    println!("=========ITERATIVOS========");

    for (name, func) in array_of_iterative {
        run::<i32, _>(array.clone(), func, String::from(name));
    }
}
