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
    cout << "Digite o ip do servidor" << endl;
    cin >> serverIP;

    cout << "Digite a porta" << endl;
   	cin >> serverPort;

	string ep = serverIP+":"+to_string(serverPort);
	cout << "Conectando a " << ep << endl;
	RestClient::Response r = RestClient::get(ep+"/transaction");
	if (r.code == -1){
		status = -1;
	} else if (r.code == 200) {
		cout << "Inicializando..." << endl;
		List* l = new List();
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
			l->append(s);
		}
		lista = l;
		status = 1;
		//lista->print();
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
		lista->print();
		cout << "Quantidade de usuarios dentro " << lista->getContador() << endl;

		cout << "Digite o comando" << endl;
		cin >> comando;

		transform(comando.begin(), comando.end(), comando.begin(),::tolower);

		entrada_saida = comando[0];
		cartao_senha = comando[1];

		if (entrada_saida == "e") {
			//ENTRADA
			if (cartao_senha == "c") {
				//ENTRADA CARTAO
				cartao = comando.substr(2,8);
				transform(cartao.begin(), cartao.end(), cartao.begin(),::toupper);
				tmp = lista->find(cartao, TipoCartao);
				if (tmp && !tmp->getData()->getStudentStatus()) {
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

			} else if (cartao_senha == "s" ) {
				//ENTRADA SENHA
				matricula = comando.substr(2,8);
				senha = comando.substr(10,4);
				tmp = lista->find(matricula,TipoMatricula);
				if (tmp && !tmp->getData()->getStudentStatus()) {
					cout << "Pessoa encontrada... Verificando senha" << endl;
					hash = md5(matricula+tmp->getData()->getSalt()+senha);
					if (hash == tmp->getData()->getPassword()) {
						cout << "Senha válida" << endl;
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
						} else  {
							cout << "Creditos insuficientes ou já está dentro do RU" << endl;
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
			//SAIDA
			if (cartao_senha == "c") {
				//SAIDA CARTAO
				cartao = comando.substr(2,8);
				transform(cartao.begin(), cartao.end(), cartao.begin(),::toupper);
				tmp = lista->find(cartao, TipoCartao);

				if (tmp && tmp->getData()->getStudentStatus()) {
					lista->decContador();
					tmp->getData()->changeStudentStatus();
				} else {
					cout << "Pessoa não encontrada ou já fora do ru" << endl;
				}
			} else if (cartao_senha == "s") {
				//SAIDA SENHA
				matricula = comando.substr(2,8);
				senha = comando.substr(10,4);
				tmp = lista->find(matricula, TipoMatricula);
				if (tmp && tmp->getData()->getStudentStatus()) {
					cout << "Pessoa encontrada... Verificando senha" << endl;
					hash = md5(matricula+tmp->getData()->getSalt()+senha);
					if (hash == tmp->getData()->getPassword()) {
						cout << "Senha válida" << endl;
						lista->decContador();
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


