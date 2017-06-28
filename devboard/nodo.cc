#ifndef NODE_CPP
#define NODE_CPP
#include "nodo.h"

template<class T>
Node<T>::Node( )
{
    ant = 0;
    prox = 0;
}

template<class T>
Node<T>::Node(T *obj)
{
    objeto = obj;
}

template<class T>
Node<T>::~Node( )
{
    prox = 0;
    ant = 0;
    delete prox;
    delete ant;
}

template<class T>
void Node<T>::setProx(Node* nod)
{
    prox = nod;
}

template<class T>
void Node<T>::setAnt(Node* nod)
{
    ant = nod;
}

template<class T>
void Node<T>::setInfo(T t)
{
    *objeto = t;
}

template<class T>
Node<T>* Node<T>::getAnt( )
{
    return ant;
}

template<class T>
Node<T>* Node<T>::getProx( )
{
    return prox;
}

template<class T>
T Node<T>::getInfo( )
{
    return *objeto;
}

/*template<class T>
void Nodo<T>::exibir( ){
	cout << objeto << endl;
}*/

#endif
