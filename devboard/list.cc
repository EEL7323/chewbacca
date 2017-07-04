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
void List::append(Student* data)
{
	int user_id = data->getUserID();
	int up = 1;
	Node<Student> *tmp = head;
	if (tmp == NULL) {
		Node<Student>* newNode = new Node<Student>();
		newNode->setData(data);
		newNode->setNext(NULL);
		head = newNode;
	} else if (tmp != NULL && tmp->getNext() == NULL) {
		if (tmp->getData()->getUserID() == user_id) {
			tmp->getData()->setCredito(tmp->getData()->getCredito()+data->getCredito());
		} else {
			Node<Student>* newNode = new Node<Student>();
			newNode->setData(data);
			newNode->setNext(NULL);
			tmp->setNext(newNode);
		}
	} else {
		while (tmp->getNext() != NULL) {
			if (tmp->getData()->getUserID() == user_id) {
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
