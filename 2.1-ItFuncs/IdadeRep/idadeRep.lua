

local function idadeRep(idade)
	local tamanho = #idade
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



local function idadeRep2(idade)
	table.sort(idade)
	return (idade[1]==idade[2]) -- Em lua as listas começam do 1 no lugar do 0
end



local function criarListaEFuncao(quantidade)

	local listaDeIdade = {}

	for i = 1, quantidade do
		table.insert(listaDeIdade,(math.random(0,100)))
	end

	print("O programa foi executado com "..quantidade.." dados.")
	for i=0,1 do
		local tempoInicial = os.clock()
		local qual = ""
		if i==0 then
			idadeRep(listaDeIdade)
			qual = "idadeRep"
		else
			idadeRep2(listaDeIdade)
			qual = "idadeRep2"
		end
		local tempoFinal = os.clock()
		local duracao = (tempoFinal - tempoInicial) * 1000

		 print(string.format("Duração do programa "..qual..": %.6f Ms", duracao))
	end
	print("")
end


print("\nExecução:")
criarListaEFuncao(100)
criarListaEFuncao(1000)
criarListaEFuncao(1000000)