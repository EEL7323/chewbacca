#include <iostream>
#include "catraca.h"
#include "restclient/restclient.h"
#include "jsonparser/json.hpp"

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
	string cartao;
	Node<Student> *tmp;
	int c;
	while(1){
		cout << endl << "Status atual dos usuarios" << endl ;
		lista->print();
		cout << "Quantidade de usuarios dentro " << lista->getContador() << endl;
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
					cout << "Credito NAO atualizado no servidor" << endl;			}
			} else {
				cout << "Creditos insuficientes ou já está dentro do RU" << endl;
			}
		} else {
			cout << "Pessoa não encontrada" << endl;
		}
	}


}


