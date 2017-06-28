#ifndef LIST_USERS_CPP
#define LIST_USERS_CPP
#include "list_users.h"
#include "list_trans.h"
using namespace std;
using json = nlohmann::json;
/*{
    "cardID": "ABCD0002",
    "event": -1,
    "timestamp": "Tue, 20 Jun 2017 12:00:25 GMT",
    "user_id": 3,
    "username": "akkauam"
  }*/


List_users::List_users()
{
    head = 0;
    tail = 0;
    cont = 0;
}

/*
List_users::List_trans(json j)
{
    int n = 0 ;
    this->head = 0;
    this->tail = 0;
    Transaction *a;
    Node<List_trans> *b;
    while(j[n] != nullptr)
    {
        a = new Transaction(j[n]["cardID"], j[n]["event"], j[n]["timestamp"], j[n]["user_id"], j[n]["username"]);
        b = new Node<List_trans>(a);
        b->getInfo().show_transaction();
        cout << j[n] << '\n';
        this->insere(b);
        n++;

    }
    //cout << j[n] << '\n';
}
*/

List_users::~List_users()
{

}

void List_users::insere(Node<List_trans>* n)
{
    if(head == 0 && tail == 0)
    {
        tail = n;
        head = n;
        cont++;
    }
    else
    {
        tail->setProx(n);
        n->setAnt(tail);
        tail = n;
        tail->setProx(0);
        cont++;
    }

}

void List_users::apaga(Node<List_trans>* n)
{
    Node<List_trans> *p,*q;
    //Node<Student>* q;
    p = n->getAnt();
    q = n->getProx();
    p->setProx(q);
    q->setAnt(p);
    delete n;
}

/*
double List_users::atualiza_saldo()
{
    Node<List_trans> *p;
    this->saldo = 0;
    p = this->head;
    while(p!=0)
    {
        this->saldo += p->getInfo().get_event();

        p = p->getProx();
    }
    return this->saldo; //ele retorna a raferencia do objeto, e caso não encontre retornará zero
}
*/

/*
double List_users::get_saldo()
{
    return this->saldo;
}
*/

/*Node<List_trans>* List_users::read()
{

}*/

unsigned long int List_users::get_cont()
{
    return cont;
}
unsigned long int List_users::atualiza_cont()
{
    Node<List_trans> *p;
    if(head !=0)
    {
        p = head;
        for(this->cont=1; p!=tail; this->cont++)
        {
            p = p->getProx();
        }
    }
    return this->cont;
}

Node<List_trans>* List_users::procura_cardID(string nome)
{
    Node<List_trans> *p;
    p = head;
    while((nome != p->getInfo().get_head()->getInfo().get_cardID()) && (p!=0))
    {
        p = p->getProx();
    }
    return p; //ele retorna a raferencia do objeto, e caso não encontre retornará zero
}

Node<List_trans>* List_users::procura_event(double event)
{
    Node<List_trans> *p;
    p = head;
    while((event != p->getInfo().get_head()->getInfo().get_event()) && (p!=0))
    {
        p = p->getProx();
    }
    return p; //ele retorna a raferencia do objeto, e caso não encontre retornará zero
}
Node<List_trans>* List_users::procura_timestamp(string timestamp)
{
    Node<List_trans> *p;
    p = head;
    while((timestamp != p->getInfo().get_head()->getInfo().get_timestamp()) && (p!=0))
    {
        p = p->getProx();
    }
    return p; //ele retorna a raferencia do objeto, e caso não encontre retornará zero
}

Node<List_trans>* List_users::procura_user_id(unsigned long int user_id)
{
    Node<List_trans> *p;
    p = head;
    while((user_id != p->getInfo().get_head()->getInfo().get_user_id()) && (p!=0))
    {
        p = p->getProx();
    }
    return p; //ele retorna a raferencia do objeto, e caso não encontre retornará zero
}

Node<List_trans>* List_users::procura_username(string username)
{
    Node<List_trans> *p;
    p = head;
    while((username != p->getInfo().get_head()->getInfo().get_username()) && (p!=0))
    {
        p = p->getProx();
    }
    return p; //ele retorna a raferencia do objeto, e caso não encontre retornará zero
}





#endif
