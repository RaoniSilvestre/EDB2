use std::cmp::Ordering;

use super::{
    auxiliary::{InsertionResult, SearchResult, RemovalResult},
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
            match key.key.cmp(&k.key) {
                Ordering::Less => {}
                Ordering::Equal => return SearchResult::Find(i),
                Ordering::Greater => return SearchResult::GoDown(i),
            }
        }
        SearchResult::GoDown(self.keys.len())
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
                self.children.insert(i + 1, new_node);
                self.children.sort();
                self.keys.insert(i, middle_key);
                self.keys.sort();

                if self.is_full() {
                    return self.split_node();
                }
            }
        }

        InsertionResult::Inserted
    }

    pub fn remove(&mut self, k: Key) -> RemovalResult {
        let result = self.search(&k);        // q chique bboy
        match result {
            SearchResult::Find(i) => {
                if self.is_leaf {
                    if self.keys.len() >= (self.grade + 1) as usize {
                        self.keys.remove(i);
                        return RemovalResult::RemoveCompleted;
                    } else { 
                        return RemovalResult::LeafRemoveFail(k);
                    } 
                } else {
                    let left_len = self.children[i].keys.len();
                    let right_len = self.children[i + 1].keys.len();

                    if left_len >= (self.grade + 1) as usize {
                        let max = self.children[i].keys.pop().unwrap();
                        self.keys[i] = max;
                        return RemovalResult::RemoveCompleted;
                    } else if right_len >= (self.grade + 1) as usize {
                        let min = self.children[i + 1].keys.remove(0);
                        self.keys[i] = min;
                        return RemovalResult::RemoveCompleted;
                    } else {
                        // Precisa fazer merge
                        todo!()
                    }
                    
                }
            },
            SearchResult::GoDown(i) => {
                let child = self.children[i].remove(k);

                // Tratar dos retornos do filho
                match child => {
                    RemovalResult::RemoveCompleted => {},
                    RemovalResult::LeafRemoveFail(failed_key) => todo!(),
                    RemovalResult::NotLeafResultFail(failed_key, new_node) => todo!()
                }
            }
        }
    }

    pub fn try_insert(&mut self, k: Key) -> InsertionResult {
        self.keys.push(k);
        self.keys.sort();

        match self.is_full() {
            true => self.split_node(),
            false => InsertionResult::Inserted,
        }
    }

    pub fn split_node(&mut self) -> InsertionResult {
        let t = self.grade as usize;
        let mid = t;

        let mut right_node = Node::new(self.is_leaf, self.grade);

        right_node.keys = self.keys.drain(mid + 1..).collect();

        if !self.is_leaf {
            right_node.children = self.children.drain(mid + 1..).collect();
        }

        let middle_key = self.keys.remove(mid);

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

    pub fn child_mut(&mut self, i: usize) -> Option<&mut Node> {
        self.children.get_mut(i)
    }

    pub fn is_full(&self) -> bool {
        self.keys.len() == (2 * self.grade + 1) as usize
    }
}
