#ifndef LIST_USERS_H
#define LIST_USERS_H

#include "transaction.h"
#include "nodo.h"
#include "nodo.cc" //preprocessador bugando e precisei dar include no node.cpp
#include <string.h>
#include "restclient/restclient.h"
#include "jsonparser/json.hpp"
#include "list_trans.h"
using namespace std;
using json = nlohmann::json;

class List_users
{

    Node<List_trans>* head;
    Node<List_trans>* tail;
    double saldo;
    unsigned long int cont;

public:
    List_users();
    //List_trans(json j);
    ~List_users();
    void insere(Node<List_trans>* n);
    void apaga(Node<List_trans>* n);
    //double atualiza_saldo();
    //double get_saldo();
    unsigned long int get_cont();
    unsigned long int atualiza_cont();
    Node<List_trans>* procura_cardID(string nome);
    Node<List_trans>* procura_event(double event);
    Node<List_trans>* procura_timestamp(string timestamp);
    Node<List_trans>* procura_user_id(unsigned long int user_id);
    Node<List_trans>* procura_username(string username);


    //Node<List_trans>* read(); Vai ler quem?
    //Node<List_trans>* procuraNome(string nome);
    //Node<List_trans>* procuraRegistro(int matri);

};



#endif // LIST_H
