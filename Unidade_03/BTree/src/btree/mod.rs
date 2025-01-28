use serde::{Deserialize, Serialize};

mod auxiliary;
mod btree;
mod display;
mod node;

#[derive(Debug, Clone)]
pub struct BTree {
    root: Node,
    grau: i32,
}

#[derive(Debug, Clone)]
pub struct Node {
    keys: Vec<Key>,
    children: Vec<Node>,
    is_leaf: bool,
    grade: i32,
}

#[derive(Debug, Clone, PartialEq, Eq, PartialOrd, Serialize)]
pub struct Key {
    key: i32,
    nome: String,
    quantidade: usize,
}
