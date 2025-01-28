use std::collections::VecDeque;
use std::fmt;

use super::{BTree, Key, Node};

impl fmt::Display for BTree {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        let mut queue = VecDeque::new();
        queue.push_back((&self.root, 0));

        let mut current_level = 0;
        write!(f, "Nível {}: ", current_level)?;

        while let Some((node, level)) = queue.pop_front() {
            if level != current_level {
                current_level = level;
                writeln!(f)?;
                write!(f, "Nível {}: \n", current_level)?;
            }

            write!(f, "{} \n", node)?;

            for child in &node.children {
                queue.push_back((child, level + 1));
            }
        }

        Ok(())
    }
}

impl fmt::Display for Node {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        write!(f, "[")?;
        for (i, key) in self.keys.iter().enumerate() {
            if i > 0 {
                write!(f, ", ")?;
            }
            write!(f, "{}", key)?;
        }
        write!(f, "]")
    }
}

impl fmt::Display for Key {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        write!(
            f,
            "{}: {} ({} unidades)",
            self.key, self.nome, self.quantidade
        )
    }
}
