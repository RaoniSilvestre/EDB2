use rusty_algoritms::generate_list;
use std::fs::File;
use std::io::Write;
use std::path::Path;

fn main() {
    let dir_path = "./data/input/";

    let file_sizes = vec![1000, 10_000, 100_000];
    let file_names = vec!["file_1000.txt", "file_10000.txt", "file_100000.txt"];

    for (i, &size) in file_sizes.iter().enumerate() {
        let numbers = generate_list(size);

        // Cria o arquivo correspondente
        let file_path = Path::new(dir_path).join(file_names[i]);
        let mut file = File::create(file_path).expect("Erro ao criar o arquivo");

        // Escreve os números no arquivo
        for number in numbers {
            writeln!(file, "{}", number).expect("Erro ao escrever no arquivo");
        }

        println!("Arquivo {} criado com sucesso!", file_names[i]);
    }
}
