#!/bin/bash

for file in ../outputDOT/arvore_de_busca*.dot; do
  nome_imagem=$(basename "$file" .dot).png
  dot -Tpng "$file" -o "../outputPNG/$nome_imagem"
  echo "Imagem gerada: ../outputPNG/$nome_imagem"
done
