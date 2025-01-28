use std::cmp::Ordering;

use super::{
    auxiliary::{InsertionResult, SearchResult},
    Key, Node,
};

impl Node {
    pub fn new(is_leaf: bool, grade: i32) -> Self {
        Node {
            children: Vec::new(),
            is_leaf,
            keys: Vec::new(),
            grade,
        }
    }

    pub fn search(&self, k: &Key) -> SearchResult {
        for (i, key) in self.keys.iter().enumerate() {
            match k.key.cmp(&key.key) {
                Ordering::Less => {}
                Ordering::Equal => return SearchResult::Find(i),
                Ordering::Greater => return SearchResult::GoDown(i),
            }
        }
        SearchResult::GoDown(self.children.len())
    }

    pub fn insert(&mut self, k: Key) -> InsertionResult {
        // Retorna o index que será buscado
        let result = self.search(&k);

        // Se é folha, acaba a recursão, apenas tenta inserir
        if self.is_leaf {
            return self.try_insert(k);
        }

        if let SearchResult::GoDown(i) = result {
            // Recursão para ir mais fundo na árvore
            let child = self.children[i].insert(k);

            if let InsertionResult::AddToFater(middle_key, new_node) = child {
                let cloned_middle_key = middle_key.clone();

                self.keys.insert(i, middle_key);
                self.children.insert(i + 1, new_node);

                if self.is_full() {
                    return self.split_node(cloned_middle_key);
                }
            }
        }

        InsertionResult::Inserted
    }

    pub fn try_insert(&mut self, k: Key) -> InsertionResult {
        match self.is_full() {
            true => self.split_node(k),
            false => self.insert_key(k),
        }
    }

    pub fn split_node(&mut self, k: Key) -> InsertionResult {
        let t = self.grade as usize;
        let mid = t - 1;

        let mut right_node = Node::new(true, self.grade);

        right_node.keys = self.keys.drain(mid + 1..).collect();

        if !self.is_leaf {
            right_node.children = self.children.drain(mid + 1..).collect();
        }

        let middle_key = self.keys.remove(mid);

        match k.key < middle_key.key {
            true => self.insert_key(k),
            false => right_node.insert_key(k),
        };

        InsertionResult::AddToFater(middle_key, right_node)
    }

    pub fn insert_key(&mut self, k: Key) -> InsertionResult {
        self.keys.push(k);
        self.keys.sort();

        InsertionResult::Inserted
    }

    pub fn key(&self, i: usize) -> Option<&Key> {
        self.keys.as_slice().get(i)
    }

    pub fn child(&self, i: usize) -> Option<&Node> {
        self.children.as_slice().get(i)
    }

    pub fn is_full(&self) -> bool {
        self.keys.len() == (2 * self.grade - 1) as usize
    }
}
