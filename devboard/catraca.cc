#include <iostream>
#include "catraca.h"
#include "restclient/restclient.h"
#include "jsonparser/json.hpp"
#include "md5.h"

using json = nlohmann::json;

int atualiza_credito_servidor(Student* s, string serverIP, int serverPort) {
	int user_id = s->getUserID();
	string ep = serverIP+":"+to_string(serverPort)+"/transaction/"+to_string(user_id);	
	RestClient::Response r = RestClient::post(ep, "application/json", "{\"event_id\": -1}");
	
	if (r.code == -1) {
		//TODO Nao conseguiu atualizar no servidor se cair aqui, criar uma lista para tentar posteriormente
		return r.code;
	} else {
		return r.code;
	}

}

Catraca::Catraca()
{
	serverIP = "";
	serverPort = 0;
	lista = NULL;
	status = 0;
}

Catraca::~Catraca()
{
	//Apagar a lista
}

int Catraca::getStatus()
{
	return status;
}


string Catraca::getServerIP()
{
	return serverIP;
}

int Catraca::getServerPort()
{
	return serverPort;
}

void Catraca::setServerIP(string serverIP)
{
	serverIP = serverIP;
}

void Catraca::setServerPort(int serverPort)
{
	serverPort = serverPort;
}

void Catraca::upServerStudentCount(int contagem)
{
	json j;
	j["v"] = contagem;
	string j2 = j.dump();
	string ep = serverIP+":"+to_string(serverPort)+"/contador";
	RestClient::Response r = RestClient::post(ep, "application/json", j2);
	if (r.code != 201) {
		cout << "Nao foi possivel alterar a contagem no servidor" << endl;
		//TODO Colocar na mesma lista da atualizacao do credito do usuario quando nao é possivel alterar o credito no servidor?
	}
}

/*
void Catraca::setList(List* lista)
{
	lista = lista;
}
*/

void Catraca::start()
{
	//Inicia os dados do servidor para conexão
    cout << "Digite o ip do servidor" << endl;
    cin >> serverIP;
    cout << "Digite a porta" << endl;
   	cin >> serverPort;

	string ep = serverIP+":"+to_string(serverPort);
	cout << "Conectando a " << ep << endl;

	//Inicialização da placa:
	/*
		Na inicialização a placa faz o "download" de todas as transações da história
		ques estão armazenadas no servidor. Uma transação é um ato de compra ou uso de crédito
		do restaurante. 
		Por exemplo, uma pessoa compra 10 créditos, é criada uma transação para o usuário em 
		questão com o valor de 10. Cada vez que um crédito é utilizado, uma transação com valor
		-1 é adicionada no servidor.
		Ao obter todas as transações, a placa consegue montar uma estrutura de dados, uma lista encadeada,
		onde guarda a informação de crédito total por usuário, fazendo a soma das transações. Além disso
		a lista guarda outras inforamções, além da contagem de pessoas dentro do restaurante.
	
		Uma transação armazenada no servidor tem o formato

		{
		    "cardID": "ABCD0000", 
		    "event": 0, 
		    "matricula": "15150162", 
		    "n_password_hash": "ae76b694cd38f7df383cd8d5403db098", 
		    "salt": "444b5430739447c09cc5bba836a7f62c", 
		    "timestamp": "Tue, 04 Jul 2017 12:33:50 GMT", 
		    "user_id": 1, 
		    "username": "andre"
  		}


		Essa lista é a parte mais importante deste trabalho.

	*/
	RestClient::Response r = RestClient::get(ep+"/transaction"); //GET no endpoint que devolve todas as transações

	if (r.code == -1){
		status = -1; //Não conseguiu conexão com o servidor, não iniciliza o resto
	} else if (r.code == 200) {
		cout << "Inicializando..." << endl;
		List* l = new List(); //Criação do objeto da classe lista
		auto j = json::parse(r.body); //Parser do body da resposta
		for (auto& element : j){
			json j2 = element;
			Student* s = new Student; //Cada item (nó/nodo) da lista principal é um objeto da classe estudante
			s->setCardID(element["cardID"]); //identificador do cartão
			s->setUserId(element["user_id"]); //identificador do usuário (único, garantido pelo servidor) 
			s->setCredito(element["event"]); //evento traz o tipo de transação que será somado para gerar o crédito
			s->setMatricula(element["matricula"]); //matricula do usuário
			s->setSalt(element["salt"]); //salt aleatório para uso da senha quando acessar o restaurante sem cartão
			s->setPassword(element["n_password_hash"]); //hash da senha original para acesso sem cartão
			l->append(s); //adiciona o objeto aluno a lista principal 
		}
		lista = l; //Atribuição do objeto ao atributo da classe
		status = 1;
	} else {
		status = -1;
	}
}

void Catraca::run()
{

	string comando;
	string cartao;
	string matricula;
	string senha;
	string hash;
	Node<Student> *tmp;
	string entrada_saida;
	string cartao_senha;
	string ep = serverIP+":"+to_string(serverPort);
	int c, e, aux;

	while(1){
		cout << endl << "Status atual dos usuarios" << endl ;
		lista->print(); //Mostra na tela os usuarios da lista e a quantidade de creditos de cada um deles
		cout << "Quantidade de usuarios dentro " << lista->getContador() << endl;

		cout << "Digite o comando" << endl;
		cin >> comando;

		transform(comando.begin(), comando.end(), comando.begin(),::tolower);

		entrada_saida = comando[0];
		cartao_senha = comando[1];

		/*Espera um comando do tipo

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

		O acesso com a senha foi criado para ser alternativa ao acesso com cartão
		O ideal seria a comunicação com o smartphone, mas devido aos problemas apresentados não foi possível planejar esse ponto

		*/


		if (entrada_saida == "e") {
			//Selecionada entrada
			if (cartao_senha == "c") {
				//Selecionada entrada com cartão
				cartao = comando.substr(2,8);
				transform(cartao.begin(), cartao.end(), cartao.begin(),::toupper);
				tmp = lista->find(cartao, TipoCartao); //Procura o usuário na lista
				if (tmp && !tmp->getData()->getStudentStatus()) {
					//Encontrou o usuário e ele está do lado de fora do restaurante (getStudentStatus())
					cout << "Pessoa encontrada" << endl;
					if (tmp->getData()->getCredito() > 0 && !tmp->getData()->getStudentStatus()) {
						//Verifica se há créditos
						tmp->getData()->setCredito(tmp->getData()->getCredito()-1); //Atualiza NA PLACA o novo crédito
						lista->incContador(tmp->getData()); //Incrementa o contador de pessoas no restaurante e altera o status do usuário para "dentro do restaurante"
						this->upServerStudentCount(lista->getContador()); //Atualiza no servidor a contagem de usuários
						cout << "AUTORIZADO... novo credito (na placa): " << tmp->getData()->getCredito() << endl;
						c = atualiza_credito_servidor(tmp->getData(), serverIP, serverPort); //Atualiza o crédito do usuário no servidor adicionando uma transação do tipo -1
			
						if (c == 201) {
							cout << "Credito atualizado no servidor" << endl;
						} else {
							//TODO: adicionar um modo de atualizar o servidor posteriormente caso a placa esteja sem conexão com o mesmo
							/*
								Como na inicialização foi criado todo o histórico dos usuários, a placa pode a partir dela, operar sozinha sem conexão com o servidor
								Não estará disponível:
									- Atualização posterior das transações (TODO)
									- Verificação de novo crédito caso o usuário compre créditos após a inicialização (IMPLEMENTADO)
									- Verificação de novo usuário cadastrado após a inicialização (IMPLEMENTADO)

							*/
							cout << "Credito NAO atualizado no servidor" << endl;			
						}
					} else {
						cout << "Creditos insuficientes ou já está dentro do RU" << endl;
						//Verificação de novos créditos comprados após a inicialização da placa
						if (!tmp->getData()->getStudentStatus()) {
							cout << "Atualizando creditos na lista interna (talvez pessoa comprou novos créditos?)" << endl;
							RestClient::Response r = RestClient::get(ep+"/transaction/"+to_string(tmp->getData()->getUserID()));
							if (r.code == -1) {
								cout << "Servidor indisponível" << endl;
							} else {
								auto j = json::parse(r.body);
								aux=0;
								e=0;
								for (auto& element : j) {
									json j2 = element;
									aux=element["event"];
									e += aux;
								}
								if (e > tmp->getData()->getCredito()) {
									cout << "Novos creditos adicionados" << endl;
									tmp->getData()->setCredito(e);
								}
							}
						}
					}
				} else if (!tmp) {
					//Não encontrou o usuário, procurando por pessoas cadastradas aspós a inicialização da placa
					cout << "Pessoa não encontrada ou não cadastrada na lista.. verificando servidor" << endl;
					RestClient::Response r = RestClient::get(ep+"/user/id/card/"+cartao);
					if (r.code == -1) {
						cout << "Servidor indisponível" << endl;
					} else {
						string user_id = r.body;
						if (user_id == "-1") {
							cout << "Pessoa inexistente" << endl;
						} else {
							RestClient::Response r = RestClient::get(ep+"/transaction/"+user_id);
							if (r.code == -1) {
								cout << "Servidor indisponível" << endl;
							} else if (r.code == 200) {
								auto j = json::parse(r.body);
								for (auto& element : j){
									json j2 = element;
									Student* s = new Student;
									s->setCardID(element["cardID"]);
									s->setUserId(element["user_id"]);
									s->setCredito(element["event"]);
									s->setMatricula(element["matricula"]);
									s->setSalt(element["salt"]);
									s->setPassword(element["n_password_hash"]);
									lista->append(s); //Adiciona novo usuário cadastrado após a inicialização da placa
								}
							} else {
								cout << "Erro inesperado" << endl;
							}
						}
					}
				} 

			} else if (cartao_senha == "s" ) {
				//Selecionada entrada com cartão
				matricula = comando.substr(2,8);
				senha = comando.substr(10,4);
				tmp = lista->find(matricula,TipoMatricula); 
				if (tmp && !tmp->getData()->getStudentStatus()) {
					//Verifica se o usuario ja está na lista e fora do restaurante
					cout << "Pessoa encontrada... Verificando senha" << endl;
					hash = md5(matricula+tmp->getData()->getSalt()+senha); //Calcula o hash da senha fornecida
					if (hash == tmp->getData()->getPassword()) {
						//Usuario validado
						cout << "Senha válida" << endl;
						if (tmp->getData()->getCredito() > 0 && !tmp->getData()->getStudentStatus()) {
							//Verifica se há créditos
							tmp->getData()->setCredito(tmp->getData()->getCredito()-1); //Atualiza na PLACA o novo crédito
							lista->incContador(tmp->getData()); //Incrementa o contador de usuarios dentro do restaurante
							this->upServerStudentCount(lista->getContador()); //Atualiza a contagem de usuarios no servidor
							cout << "AUTORIZADO... novo credito (na placa): " << tmp->getData()->getCredito() << endl;
							c = atualiza_credito_servidor(tmp->getData(), serverIP, serverPort); //Atualiza o credito com uma nova transação do usuario no servidor
							if (c == 201) {
								cout << "Credito atualizado no servidor" << endl;
							} else {
								/*
									Idem comentário anterior sobre conexão com a placa
								*/
								cout << "Credito NAO atualizado no servidor" << endl;			
							}
						} else  {
							cout << "Creditos insuficientes ou já está dentro do RU" << endl;
							//Faz a verificação de creditos comprados após a inicialização da placa
							if (!tmp->getData()->getStudentStatus()) {
								cout << "Atualizando creditos na lista interna (talvez pessoa comprou novos créditos?)" << endl;
								RestClient::Response r = RestClient::get(ep+"/transaction/"+to_string(tmp->getData()->getUserID()));
								if (r.code == -1) {
									cout << "Servidor indisponível" << endl;
								} else {
									auto j = json::parse(r.body);
									aux=0;
									e=0;
									for (auto& element : j) {
										json j2 = element;
										aux=element["event"];
										e += aux;
									}
									if (e > tmp->getData()->getCredito()) {
										cout << "Novos creditos adicionados" << endl;
										tmp->getData()->setCredito(e);
									}
								}
							}
						}
					} else {
						cout << "Senha inválida" << endl;
					}
				} else if (!tmp) {
					//Não encontrou a pessoa na lista inicializada
					//Verifica se foi cadastrada após a inicizalização e adiciona na lista
					cout << "Pessoa não encontrada ou não cadastrada na lista.. verificando servidor" << endl;
					RestClient::Response r = RestClient::get(ep+"/user/id/card/"+cartao);
					if (r.code == -1) {
						cout << "Servidor indisponível" << endl;
					} else {
						string user_id = r.body;
						if (user_id == "-1") {
							cout << "Pessoa inexistente" << endl;
						} else {
							RestClient::Response r = RestClient::get(ep+"/transaction/"+user_id);
							if (r.code == -1) {
								cout << "Servidor indisponível" << endl;
							} else if (r.code == 200) {
								auto j = json::parse(r.body);
								for (auto& element : j){
									json j2 = element;
									Student* s = new Student;
									s->setCardID(element["cardID"]);
									s->setUserId(element["user_id"]);
									s->setCredito(element["event"]);
									s->setMatricula(element["matricula"]);
									s->setSalt(element["salt"]);
									s->setPassword(element["n_password_hash"]);
									lista->append(s);
								}
							} else {
								cout << "Erro inesperado" << endl;
							}
						}
					}
				}
			} else {
				cout << "Comando inválido" << endl;
			}
		} else if (entrada_saida == "s") {
			//Saída
			if (cartao_senha == "c") {
				//Selecionado saída com cartão
				cartao = comando.substr(2,8);
				transform(cartao.begin(), cartao.end(), cartao.begin(),::toupper);
				tmp = lista->find(cartao, TipoCartao);

				if (tmp && tmp->getData()->getStudentStatus()) {
					lista->decContador(); //Decrementa o contador de usuarios dentro do restaurante
					tmp->getData()->changeStudentStatus(); //Altera o status do usuario para "fora do restaurante"
				} else {
					cout << "Pessoa não encontrada ou já fora do ru" << endl;
				}
			} else if (cartao_senha == "s") {
				//Selecionado saída com senha
				matricula = comando.substr(2,8);
				senha = comando.substr(10,4);
				tmp = lista->find(matricula, TipoMatricula);
				if (tmp && tmp->getData()->getStudentStatus()) {
					cout << "Pessoa encontrada... Verificando senha" << endl;
					hash = md5(matricula+tmp->getData()->getSalt()+senha); //Verifica a senha válida
					if (hash == tmp->getData()->getPassword()) {
						cout << "Senha válida" << endl;
						lista->decContador(); //Decrementa o contador
						tmp->getData()->changeStudentStatus();
					} else {
						cout << "Senha inválida" << endl;
					}
				} else {
					cout << "Pessoa não encontrada ou já fora do ru" << endl;
				}
			} else {
				cout << "Comando inválido";
			}
		} else {
			cout << "Comando inválido" << endl;
		}

/*
		cout << "Digite o cartão" << endl;
		cin >> cartao;
		transform(cartao.begin(), cartao.end(), cartao.begin(),::toupper);

		//TODO Diferenciar quando a pessoa entra e sai do restaurante e chamar List::decContador(Student* s) quando alguém sair
		//TODO Fazer com que a ideia de senha funcione?
		tmp = lista->find(cartao);
		if (tmp) {
			cout << "Pessoa encontrada" << endl;
			if (tmp->getData()->getCredito() > 0 && !tmp->getData()->getStudentStatus()) {
				tmp->getData()->setCredito(tmp->getData()->getCredito()-1);
				lista->incContador(tmp->getData());
				this->upServerStudentCount(lista->getContador());
				cout << "AUTORIZADO... novo credito (na placa): " << tmp->getData()->getCredito() << endl;
				c = atualiza_credito_servidor(tmp->getData(), serverIP, serverPort); 
	
				if (c == 201) {
					cout << "Credito atualizado no servidor" << endl;
				} else {
					cout << "Credito NAO atualizado no servidor" << endl;			
				}
			} else {
				cout << "Creditos insuficientes ou já está dentro do RU" << endl;
			}
		} else {
			cout << "Pessoa não encontrada" << endl;
		}
		*/
	}
	
}


