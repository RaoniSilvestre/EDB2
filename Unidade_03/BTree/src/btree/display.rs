use std::fmt;

use super::{BTree, Key, Node};

impl fmt::Display for BTree {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        fn display_node(node: &Node, f: &mut fmt::Formatter<'_>, level: usize) -> fmt::Result {
            // Adiciona indentação para mostrar o nível do nó
            for _ in 0..level {
                write!(f, "    ")?; // 4 espaços para cada nível
            }

            // Exibe o nó atual
            writeln!(f, "Nó: {}", node)?;

            // Exibe os filhos do nó recursivamente
            for child in &node.children {
                display_node(child, f, level + 1)?;
            }

            Ok(())
        }

        // Começa com o nó raiz
        writeln!(f, "Árvore B:")?;
        display_node(&self.root, f, 0)?;

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
            write!(f, "{}", key.key)?;
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
