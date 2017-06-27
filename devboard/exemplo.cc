#include <iostream>
#include "restclient/restclient.h"
#include "jsonparser/json.hpp"
#include <string>

using json = nlohmann::json;
using namespace std;

class Student {
	string cardID;
	int userId;
	int credito;
public:
	Student() { credito = 0; };
	string getCardID() { return cardID; };
	int getUserId() { return userId; };
	int getCredito() { return credito; };
	void setCardID(string s) { cardID = s; };
	void setUserId(int i) { userId = i; };
	void setCredito(int i) { credito = i; };
};

class Node {
	Student* data;
	Node* next;
public:
	Node() {};
	void SetData(Student* aData) { data = aData; };
	void SetNext(Node* aNext) { next = aNext; };
	Student* Data() { return data; };
	Node* Next() { return next; };
};

class List {
	Node *head;
public:
	List() { head = NULL; };
	Node* Find(string cardID);
	void Print();
	void Append(Student* data);
	void Delete(Student* data);
};

Node* List::Find(string s) {
	Node *tmp = head;
	if (tmp == NULL) {
		return NULL;
	}

	if (tmp->Next() == NULL) {
		if (tmp->Data()->getCardID() == s) {
			return tmp;
		} else {
			return NULL;
		}
	} else {
		while (tmp != NULL) {
			if (tmp->Data()->getCardID() == s) {
				return tmp;
			}
			tmp = tmp->Next();
		}

		return NULL;
	}
}

void List::Print() {

	// Temp pointer
	Node *tmp = head;

	// No nodes
	if ( tmp == NULL ) {
		cout << "EMPTY" << endl;
		return;
	}

	// One node in the list
	if ( tmp->Next() == NULL ) {
		cout << tmp->Data()->getUserId() << " "  << tmp->Data()->getCredito() << endl;
	}
	else {
	// Parse and print the list
		do {
			cout << tmp->Data()->getUserId() << " "  << tmp->Data()->getCredito() << endl;
			tmp = tmp->Next();
		} while ( tmp != NULL );

	
	}
}
void List::Append(Student* data){
	int user_id = data->getUserId();
	int up = 1;
	Node *tmp = head;
	if (tmp == NULL) {
		Node* newNode = new Node();
		newNode->SetData(data);
		newNode->SetNext(NULL);
		head = newNode;
	} else if (tmp != NULL && tmp->Next() == NULL) {
		if (tmp->Data()->getUserId() == user_id) {
			tmp->Data()->setCredito(tmp->Data()->getCredito()+data->getCredito());
		} else {
			Node* newNode = new Node();
			newNode->SetData(data);
			newNode->SetNext(NULL);
			tmp->SetNext(newNode);
		}
	} else {
		while (tmp->Next() != NULL) {
			if (tmp->Data()->getUserId() == user_id) {
				tmp->Data()->setCredito(tmp->Data()->getCredito()+data->getCredito());
				up = 0;
				break;
			}
			tmp = tmp->Next();
		}
		if (up == 1) {
			if (tmp->Data()->getUserId() == user_id) {
				tmp->Data()->setCredito(tmp->Data()->getCredito()+data->getCredito());
			} else {
				Node* newNode = new Node();
				newNode->SetData(data);
				newNode->SetNext(NULL);
				tmp->SetNext(newNode);
			}
		}
	}
}

/**
 * Delete a node from the list
 */
void List::Delete(Student* data) {

	// Create a temp pointer
	Node *tmp = head;

	// No nodes
	if ( tmp == NULL )
		return;

	// Last node of the list
	if ( tmp->Next() == NULL ) {
		delete tmp;
		head = NULL;
	}
	else {
		// Parse thru the nodes
		Node *prev;
		do {
			if ( tmp->Data() == data ) break;
			prev = tmp;
			tmp = tmp->Next();
		} while ( tmp != NULL );

		// Adjust the pointers
		prev->SetNext(tmp->Next());

		// Delete the current node
		delete tmp;
	}
}

/*
###TODO###
caso nao consiga conexao com o server, criar uma especie  de "lista" de atualizacao dentro do programa
*/
int atualiza_credito_servidor(Student* s) {
	int user_id = s->getUserId();
	string ep = "http://cluster.linse.ufsc.br:5000/transaction/"+to_string(user_id);
	RestClient::Response r = RestClient::post(ep, "application/json", "{\"event_id\": -1}");
	if (r.code == -1) {
		//ADICIONA NA LISTA PRA ATUALIZAR
		return r.code;
	} else {
		return r.code;
	}
	
}


int main()
{   
	RestClient::Response r = RestClient::get("http://cluster.linse.ufsc.br:5000/transaction");
	//std::cout << r.code;
	
	if (r.code == -1) {
		cout << "SERVIDOR NAO RESPONDE... NAO É POSSÍVEL INICIAR" << endl;
		return 1;
	}
	auto j = json::parse(r.body);
	List l;
	for (auto& element : j) 
	{
		Student* s = new Student;
		json j2 = element;
		//std::cout << j2["username"] << std::endl;
		s->setCardID(j2["cardID"]);
		s->setUserId(j2["user_id"]);
		s->setCredito(j2["event"]);
		//cout << "SERVER_DATA: " << s->getUserId() << " " << s->getCredito() << endl;
		l.Append(s);
	}
	l.Print();
	while (1){ 
		string cartao;
		cout << "DIGITE O CARTAO" << endl;
		cin >> cartao;
		cout << cartao << endl;
		Node *tmp = l.Find(cartao);
		if (!tmp) {
			cout << "PESSOA NAO ENCONTRADA" << endl;
		} else {
			cout << "PESSOA ENCONTRADA "<< endl;
			if (tmp->Data()->getCredito() > 0) {
				tmp->Data()->setCredito(tmp->Data()->getCredito()-1); 
				cout << "AUTORIZADO... novo credito: " << tmp->Data()->getCredito() <<endl;
				int c = atualiza_credito_servidor(tmp->Data());
				cout << "CODIGO ATUALIZACAO " << c << endl;
				if (c == 201) {
					cout << "CREDITO ATUALIZADO NO SERVER" << endl;
				} else {
					cout << "CREDITO NAO ATUALIZADO NO SERVER" << endl;
				}
			} else {
				cout << "CREDITOS INSUFICIENTES" << endl;
			}
		}
	} 
	return 0;
}

