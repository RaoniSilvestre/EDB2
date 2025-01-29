use super::{
    auxiliary::{InsertionResult, SearchResult},
    BTree, Key, Node,
};

impl BTree {
    pub fn new(g: i32) -> Self {
        BTree {
            root: Node::new(true, g),
            grau: g,
        }
    }

    pub fn find(&self, k: Key) -> Option<Key> {
        let mut curr_node = &self.root;
        loop {
            match curr_node.search(&k) {
                SearchResult::Find(i) => return curr_node.key(i).cloned(),
                SearchResult::GoDown(i) => match curr_node.child(i) {
                    None => return None,
                    Some(next_node) => curr_node = next_node,
                },
            }
        }
    }

    pub fn insert(&mut self, k: Key) {
        let insertion = self.root.insert(k);

        if let InsertionResult::AddToFater(k, new_node) = insertion {
            *self = Self::new_root(self.root.clone(), k, new_node);
        }
    }
    
    pub fn remove(&mut self, k: Key) {
        if self.find(k.clone()) == None {
            return;
        }

        let mut curr_node = &mut self.root;
        loop {
            match curr_node.search(&k) {
                SearchResult::Find(i) => {
                    if curr_node.is_leaf {
                        if curr_node.keys.len() >= (self.grau + 1) as usize {
                            curr_node.keys.remove(i);
                            return;
                        } else {
                            // Nó não folha e com menos chaves que o mínimo se remover alguma
                            return;
                        }
                    } else {
                        // Nó não folha
                        let left_len = curr_node.child(i).unwrap().keys.len();
                        let right_len = curr_node.child(i + 1).unwrap().keys.len();

                        if left_len >= (self.grau + 1) as usize {
                            let max = curr_node.child_mut(i).unwrap().keys.pop().unwrap();
                            curr_node.keys[i] = max;
                            return;
                        } else if right_len >= (self.grau + 1) as usize {
                            let min = curr_node.child_mut(i + 1).unwrap().keys.remove(0);
                            curr_node.keys[i] = min;
                            return;
                        } else {
                            // Nenhum dos irmãos tem chaves suficientes
                            // Precisa fazer um merge
                        }
                    }
                }
                SearchResult::GoDown(i) => match curr_node.child_mut(i) {
                    None => return,
                    Some(next_node) => curr_node = next_node,
                },
            }
        }
    }

    fn new_root(root: Node, k: Key, new_node: Node) -> Self {
        let mut new_root = Node::new(false, root.grade);

        new_root.keys.push(k);

        new_root.children.push(root);
        new_root.children.push(new_node);

        Self {
            grau: new_root.grade,
            root: new_root,
        }
    }
}
