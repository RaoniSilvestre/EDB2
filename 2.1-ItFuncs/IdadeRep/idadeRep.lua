local function idadeRep(idade)
	local tamanho = #idade
	local menor = 200

	for i = 1,tamanho do
		if idade[i] < menor then
			menor = idade[i]
		end
	end

	for i = 1,tamanho do
		if idade[i] == menor then
			return true
		end
	end

	return false
end



local function idadeRep2(idade)
	table.sort(idade)
	return (idade[1]==idade[2])
end



local function criarListaEFuncao(quantidade, opcao)
	
	local tempoInicial = os.clock()

	local listaDeIdade = {}

	for i = 1, quantidade do
		table.insert(listaDeIdade,(math.random(0,100)))
	end
	

	if opcao then
		idadeRep(listaDeIdade)
	else
		idadeRep2(listaDeIdade)
	end

	
	local tempoFinal = os.clock()
	local duracao = tempoFinal - tempoInicial

	print(string.format("O programa foi executado com "..quantidade.." dados. Duração do programa: %.6f segundos", duracao))

end


print("\nExecução com idadeRep:")
criarListaEFuncao(100, true)
criarListaEFuncao(1000, true)
criarListaEFuncao(1000000, true)
print("\nExecução com idadeRep2:")
criarListaEFuncao(100, false)
criarListaEFuncao(1000, false)
criarListaEFuncao(1000000, false)