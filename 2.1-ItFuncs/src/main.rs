use rand::Rng;
use std::time::Instant;

fn idade_rep(idades: &[u32]) -> bool {
    let mut idade_minima: u32 = 100;
    let mut minimo_indice: usize = 0;

    for (i, &idade) in idades.into_iter().enumerate() {
        if idade < idade_minima {
            idade_minima = idade;
            minimo_indice = i;
        }
    }

    for (i, &idade) in idades.into_iter().enumerate() {
        if idade == idade_minima && i != minimo_indice {
            return true;
        }
    }

    false
}

fn idade_rep_2(idades: &mut [u32]) -> bool {
    idades.sort();
    idades[0] == idades[1]
}

fn run(tamanho: usize) {
    let mut idades = random_generator(tamanho);

    let start_1 = Instant::now();
    let r1 = idade_rep(&mut idades);
    let duration_r1 = start_1.elapsed();

    let start_2 = Instant::now();
    let r2 = idade_rep_2(&mut idades);
    let duration_r2 = start_2.elapsed();

    println!("------------------------");
    println!("Idade_rep   ; {} {} => {:?}", tamanho, r1, duration_r1);
    println!("Idade_rep_2 ; {} {} => {:?}", tamanho, r2, duration_r2);
}

fn random_generator(n: usize) -> Vec<u32> {
    let mut idades = Vec::new();
    let mut rng_1 = rand::thread_rng();
    for _ in 0..n {
        let new_idade = rng_1.gen_range(1..100);
        idades.push(new_idade)
    }
    idades
}

fn main() {
    let n_100 = 100;
    let n_1k = 1_000;
    let n_1m = 1_000_000;

    run(n_100);
    run(n_1k);
    run(n_1m);
}
