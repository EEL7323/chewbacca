#ifndef LIST_TRANS_CPP
#define LIST_TRANS_CPP
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

/*
List::List()
{
  head = 0;
  tail = 0;
}*/

List_trans::List_trans(json j)
{
    int n = 0 ;
    this->head = 0;
    this->tail = 0;
    Transaction *a;
    Node<Transaction> *b;
    while(j[n] != nullptr)
    {
        a = new Transaction(j[n]["cardID"], j[n]["event"], j[n]["timestamp"], j[n]["user_id"], j[n]["username"]);
        b = new Node<Transaction>(a);
        b->getInfo().show_transaction();
        cout << j[n] << '\n';
        this->insere(b);
        n++;

    }
    //cout << j[n] << '\n';
}


List_trans::~List_trans()
{

}

void List_trans::insere(Node<Transaction>* n)
{
    if(head == 0 && tail == 0)
    {
        tail = n;
        head = n;
    }
    else
    {
        tail->setProx(n);
        n->setAnt(tail);
        tail = n;
        tail->setProx(0);
    }

}

void List_trans::apaga(Node<Transaction>* n)
{
    Node<Transaction> *p,*q;
    //Node<Student>* q;
    p = n->getAnt();
    q = n->getProx();
    p->setProx(q);
    q->setAnt(p);
    delete n;
}

double List_trans::atualiza_saldo()
{
    Node<Transaction> *p;
    if(head !=0)
    {
        this->saldo = 0;
        p = this->head;
        while(p!=0)
        {
            this->saldo += p->getInfo().get_event();

            p = p->getProx();
        }
        return this->saldo; //ele retorna a raferencia do objeto, e caso não encontre retornará zero
    }
    else
    {
        return -1;
    }
}

double List_trans::get_saldo()
{
    return this->saldo;
}
void List_trans::show_all_transactions()
{
    Node<Transaction> *p;
    if(head !=0)
    {
        p = this->head;
        while(p!=0)
        {
            p->getInfo().show_transaction();
            p = p->getProx();
        }
    }
    else
    {
        cout << "usuario sem transacoes";
    }

}

Node<Transaction>* List_trans::get_head()
{
    return this->head;
}
Node<Transaction>* List_trans::get_tail()
{
    return this->tail;
}

/*Node<Student>* List::read()
{

}*/

/*Node<Transaction>* List::procuraNome(string nome)
{
    Node<Transaction> *p;
    p = head;
    while((nome == p->getInfo().getName()) && (p!=tail))
    {
        p = p->getProx();
    }
    return p; //ele retorna a raferencia do objeto, e caso não encontre retornará zero
}

Node<Transaction>* List::procuraRegistro(int matri)
{
    Node<Transaction> *p;
    p = head;
    while((p->getInfo().getRegistration() != matri) && (p!=tail))
    {
        p = p->getProx();
    }
    return p; //ele retorna a raferencia do objeto, e caso não encontre retornará zero
}

*/


#endif
