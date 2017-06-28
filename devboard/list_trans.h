#ifndef LIST_TRANS_H
#define LIST_TRANS_H

#include "transaction.h"
#include "nodo.h"
#include "nodo.cc" //preprocessador bugando e precisei dar include no node.cpp
#include <string.h>
#include "restclient/restclient.h"
#include "jsonparser/json.hpp"
using namespace std;
using json = nlohmann::json;

class List_trans
{

    Node<Transaction>* head;
    Node<Transaction>* tail;
    double saldo;

public:
    //List();
    List_trans(json j);
    ~List_trans();
    void insere(Node<Transaction>* n);
    void apaga(Node<Transaction>* n);
    double atualiza_saldo();
    double get_saldo();
    void show_all_transactions();
    Node<Transaction>* get_head();
    Node<Transaction>* get_tail();

    //Node<Student>* read(); Vai ler quem?
    //Node<Transaction>* procuraNome(string nome);
    //Node<Transaction>* procuraRegistro(int matri);

};



#endif // LIST_H
