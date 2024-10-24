A conclusão que tiramos da comparação entre as duas funções e seus tempos de execução é a seguinte:

A função idadeRep percorre a lista duas vezes:

O primeiro for percorre a lista para encontrar o menor valor, com complexidade de O(n), onde n é o tamanho da lista.
O segundo for verifica se o menor valor se repete, também com complexidade O(n), podendo ser interrompido antecipadamente ao encontrar o menor valor.
Portanto, a complexidade de idadeRep é O(2n) = O(n), o que é linear.

Por outro lado, a função idadeRep2 ordena a lista e faz uma comparação:

A chamada a table.sort() ordena a lista com complexidade, no melhor dos casos, O(n log n), isso porque não foi encontrado especificamente qual algoritmo de ordenação a linguagem usa.
Em seguida, há uma comparação entre os dois primeiros elementos, uma operação de custo constante.
Assim, a complexidade de idadeRep2 é O(n log n).


À medida que a lista cresce, a diferença começa a aparecer. A idadeRep2 começa a ser notavelmente mais lenta porque a ordenação envolve mais operações do que o simples percurso linear de idadeRep.
Com 1.000.000 de elementos, a diferença é ainda mais evidente. A função idadeRep (linear) tem um tempo de execução muito menor que idadeRep2, que é O(n log n). Isso reflete a diferença assintótica entre O(n) e O(n log n). A ordenação vai se tornando muito mais custosa à medida que o tamanho da entrada aumenta.

Portanto, idadeRep é mais eficiente assintoticamente, como evidenciado pelos tempos de execução menores à medida que a quantidade de dados aumenta.
