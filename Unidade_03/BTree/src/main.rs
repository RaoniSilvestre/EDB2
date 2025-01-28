use std::{
    fs::File,
    io::{BufRead, BufReader},
};

use btree::{BTree, Key};

fn main() {
    let mut b = BTree::new(2);

    let file = File::open("dadosB.txt").unwrap();
    let reader = BufReader::new(file);

    let keys: Vec<Key> = reader
        .lines()
        .map(|line| line.unwrap())
        .map(|line| serde_plain::from_str(&line.trim()).unwrap())
        .collect();

    for key in keys {
        b.insert(key);
    }

    println!("{}", b);
}
