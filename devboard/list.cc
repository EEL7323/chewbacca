#include <iostream>
#include "list.h"

List::List()
{
	head = NULL;
	contadorStudentIn = 0;
}

List::~List()
{
	head = NULL;
	delete head;
}

void List::updateContador()
{
	contadorStudentIn = 0;
	Node<Student>* tmp = head;
	while (tmp != NULL) {
		if (tmp->getData()->getStudentStatus()) {
			contadorStudentIn++;
		}
	}
}

void List::incContador(Student* s)
{
	contadorStudentIn++;
	s->changeStudentStatus();
}

void List::decContador()
{
	contadorStudentIn--;
}

int List::getContador()
{
	return contadorStudentIn;
}

/*
	Encontra na lista um node do tipo Student
	Executa as buscas pela matrícula ou pelo identificador do cartão
*/
Node<Student>* List::find(string s, TipoBusca tipo) 
{
	Node<Student> *tmp = head;
	if (tmp == NULL) {
		return NULL;
	}

	if (tmp->getNext() == NULL) {
		if (tipo == TipoCartao) {
			if (tmp->getData()->getCardID() == s) {
				return tmp;
			} else {
				return NULL;
			}
		} else if (tipo == TipoMatricula) {
			if (tmp->getData()->getMatricula() == s) {
				return tmp;
			} else {
				return NULL;
			}
		} else {
			return NULL;
		}
			
	} else {
		while (tmp != NULL) {
			if (tipo == TipoCartao) {
				if (tmp->getData()->getCardID() == s) {
					return tmp;
				}
			} else if (tipo == TipoMatricula) {
				if (tmp->getData()->getMatricula() == s) {
					return tmp;
				}
			} else {
				return NULL;
			}
			tmp = tmp->getNext();
		}

		return NULL;
	}
}

/*
	Imprime na tela as informações de identificação do usuário e crédito total 
	disponível na lista principal
*/
void List::print() 
{

	Node<Student> *tmp = head;

	if ( tmp == NULL ) {
		cout << "EMPTY" << endl;
		return;
	}

	if ( tmp->getNext() == NULL ) {
		cout << "User " << tmp->getData()->getUserID() << " Credito "  << tmp->getData()->getCredito() << endl;
	}
	else {
		do {
			cout << "User " << tmp->getData()->getUserID() << " Credito "  << tmp->getData()->getCredito() << endl;
			tmp = tmp->getNext();
		} while ( tmp != NULL );

	
	}
}

/*
	Adiciona um novo node, do tipo estudante, a lista

	Funcionamento básico:
	Adiciona um usuario novo na lista. Se o usuário já estiver na lista, atualiza o valor do crédito com o novo evento
*/
void List::append(Student* data)
{
	int user_id = data->getUserID();
	int up = 1;
	Node<Student> *tmp = head; //ponteiro para o inicio da lista
	if (tmp == NULL) {
		//Lista vazia
		Node<Student>* newNode = new Node<Student>(); //Define um novo nodo do tipo estudante
		newNode->setData(data);
		newNode->setNext(NULL);
		head = newNode; //Cria o head da lista
	} else if (tmp != NULL && tmp->getNext() == NULL) {
		//Só existe um nodo na lista
		if (tmp->getData()->getUserID() == user_id) {
			//Caso esteja adicionando um usuário que já está na lista, apenas atualiza com a nova transação
			tmp->getData()->setCredito(tmp->getData()->getCredito()+data->getCredito());
		} else {
			//O segundo usuário adicionado é diferente do primeiro, então cria um novo nodo
			Node<Student>* newNode = new Node<Student>();
			newNode->setData(data);
			newNode->setNext(NULL);
			tmp->setNext(newNode);
		}
	} else {
		//A lista já possui o primeiro e o segundo nodo
		while (tmp->getNext() != NULL) {
			//Verifica nodo por nodo para ver se o usuário ja está inserido
			if (tmp->getData()->getUserID() == user_id) {
				//Atualiza o credito caso encontre
				tmp->getData()->setCredito(tmp->getData()->getCredito()+data->getCredito());
				up = 0;
				break;
			}
			tmp = tmp->getNext();
		}
		if (up == 1) {
			if (tmp->getData()->getUserID() == user_id) {
				tmp->getData()->setCredito(tmp->getData()->getCredito()+data->getCredito());
			} else {
				//Adiciona um novo caso nao encontre na lista inteira
				Node<Student>* newNode = new Node<Student>();
				newNode->setData(data);
				newNode->setNext(NULL);
				tmp->setNext(newNode);
			}
		}
	}
}

void List::apaga(Student* data)
{

	Node<Student> *tmp = head;

	if ( tmp == NULL )
		return;

	if ( tmp->getNext() == NULL ) {
		delete tmp;
		head = NULL;
	}
	else {
		Node<Student> *prev;
		do {
			if ( tmp->getData() == data ) break;
			prev = tmp;
			tmp = tmp->getNext();
		} while ( tmp != NULL );

		prev->setNext(tmp->getNext());

		delete tmp;
	}
}
