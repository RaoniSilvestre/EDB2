

-- A função idadeRep inicialmente  percorre toda a lista para determinar o menor numero presente (caso haja um numero menor que 200)
-- Após isso ela percorre a lista novamente para reencontrar o menor numero
-- Caso o menor numero da lista sejá menor que 200, ele retorna verdadeiro quando ô encontrar
-- Caso o menor numero da lista sejá maior que 200, ela retorna falso
-- A função tem complexidade linear, e sua interrupção depende da posição do menor numero da lista (caso haja um numero menor que 200 presente)

local function idadeRep(idade)
	local tamanho = #idade   -- Em lua usamos # antes de uma lista para obtermos o tamanho dela, assim como o .size()
	local menor = 200

	for i = 1,tamanho do
		if idade[i] < menor then
			menor = idade[i]
		end
	end

	for i = 1,tamanho do      -- Em lua os For's acabam quando o indice fica maior que o limite (neste caso quando i for maior que tamanho)
		if idade[i] == menor then
			return true
		end
	end

	return false
end

-- A função idadeRep2 inicialmente ordena toda a lista recebida
-- E após isso retorna o resultado da verificação do primeiro e segundo numero serem iguais
-- No final a maior parte da complexidade da função deriva da ordenação da lista, já que a comparação feita em seguida é constante

local function idadeRep2(idade)
	table.sort(idade)           -- Em lua, a função de ordenação de listas se da por table.sort(nomeDaLista)
	return (idade[1]==idade[2]) -- Em lua as listas começam do 1 no lugar do 0
end



-- A função criarListaEFuncao é ultilizada para executar a tarefa de
-- Fazer os inputs solicitados e computar os tempos de execução
-- Criando uma lista aleatoria e a passando para as duas funções

local function criarListaEFuncao(quantidade) -- A variavel quantidade define o tamanho da lista

	local listaDeIdade = {}

	for i = 1, quantidade do
		table.insert(listaDeIdade,(math.random(0,100)))  -- Cria numeros aleatorios de 0 a 100 para compor a lista
	end

	print("O programa foi executado com "..quantidade.." dados.")

	for i=0,1 do                                -- É ultilizado For para obtermos os resultados dos dois tempos com a mesma lista
		local tempoInicial = os.clock()         -- Variavel para obter às horas que o programa começou a executar as funções
		local qual = ""
		if i==0 then
			idadeRep(listaDeIdade)
			qual = "idadeRep"
		else
			idadeRep2(listaDeIdade)
			qual = "idadeRep2"
		end
		local tempoFinal = os.clock()          -- Variavel para obter às horas que o programa finalizou de executar as funções
		local duracao = (tempoFinal - tempoInicial) * 1000  -- A diferença das duas variaveis/ O tempo de execução

		 print(string.format("Duração do programa "..qual..": %.6f Ms", duracao))
	end
	print("")
end


print("\nExecução:")
criarListaEFuncao(100)
criarListaEFuncao(1000)       -- Executando os inputs com diferentes tamanhos de lista
criarListaEFuncao(1000000)