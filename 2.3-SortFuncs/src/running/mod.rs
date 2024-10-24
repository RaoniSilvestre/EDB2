use std::{fmt::Display, fs::File, io::Write, path::Path, time::Instant};

use crate::sorting::OrderedCopy;

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
