# Guia de Uso

## servidor:

	cd server/
	install.sh

Este arquivo instalará os pacotes básicos e criará um ambiente virtual do python de onde rodará o servidor. No ambiente virtual os pacotes necessários do projeto serão instalados e a inicialização e criação do servidor serão feitas.

A inicialização colocará algumas informações no banco de dados para demonstrações.

	./run.py --host=host --port=port

Iniciará o servidor.

 * host=localhost (default) para todar na mesma máquina
 * host=0.0.0.0 para responder através do IP da máquina
 * port=5000 (default)

## catraca - placa:

	libcurl  
 Dependência externa necessária em /usr/lib/x86_64-linux-gnu normalmente disponível via libcurl4-openssl-dev.
 
 	cd devboard/
 	make
 Compila os códigos fonte do projeto
 
 	./placa
 Com o servidor acima rodando, inicializará o funcionamento da catraca.
 
 ### Funcionamento
 
 Inserir os dados como endereço do servidor e porta.
    
    	Espera um comando do tipo

		(e|s)(c|s)(dados)

		onde:
			primeiro campo: e - entrada
							s - saida
			segunda campo : c - cartão
							s - senha
			terceiro campo: dados referentes as opções anteriores
				cartão formato: abcd0000
				senha formato: matricula+senha -> 151501620000

		Exemplo:

		ecabcd0000 - entrada com cartão, e identificador do cartao "abcd0000"
		ss151501620000 - saida com a senha, onde a matricula é 15150162 e a senha é 0000
        
  #### Desktop App
  
  Fazer o build do projeto no qtCreator (não houve tempo de criar o executável final)
    
  No lado esquerdo é possível cadastrar usuários. Importante memorizar ou anotar os dados inseridos para usá-los na placa em seguida. IMPORTANTE: cadastrar o cartão no formato ABCD01234 com as letras em maiúsculo para consistência do projeto, pois não foi possível corrigir todas as situações.
  
  No lado direito insere-se créditos através da informação do cartão e quantidade de crédito (passe), e não por valor.
  
  O app pode funcionar ao mesmo tempo que a placa e deve estar conectado ao servidor (servidor deve estar rodando na mesma maquina que o app). Pessoas recém cadastradas ou com crédito zerado que inseriram créditos após a inicialização da placa, devem inserir seus dados para acesso ao restaurante duas vezes. A primeira os busca no servidor e a segunda efetua a entrada conforme mensagens aparecem na tela.
  
  
 # TODO
 
  * Fazer com que a placa atualize o servidor quando a conexão cai
  * tornar o desktop-app um executável e deixa-lo mais configurável
  * Tratar mais casos de inconsistência na entrada dos dados
  * Alterar a forma de entrada de dados para acesso
  * Tornar o servidor e o banco de dados mais amigável, onde seja possível ver as informações armazenadas principalmente

#### Projetos externos utilizados
 * Json parser - https://github.com/nlohmann/json
 * C++ RestClient - https://github.com/mrtazz/restclient-cpp
 * RFC1321 (MD5) - http://www.bzflag.org