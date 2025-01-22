pub struct BTree {
    // !NOTA: i32 == int
    pub chaves: Vec<i32>,
    // !NOTA: Box<T> em rust é o mesmo de *T em C++
    pub filhos: Vec<Box<BTree>>,
    pub is_leaf: bool,
    pub grau: i32,
}
