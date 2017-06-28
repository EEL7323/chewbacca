#ifndef CATRACA_CPP
#define CATRACA_CPP

#include "catraca.h"
using namespace std;
using json = nlohmann::json;



void Catraca::requisita_IP()
{
    cout << "digite o IP do servidor (com os pontos): ";

    cin >> IP;
    cout << "oi";
    IP += ":5000/";
}

void Catraca::servidor_funcionando()
{
    this->r = RestClient::get(IP);

    cout << this->r.code << '\n' << this->r.body << '\n';
}

void Catraca::entrada_cardID()
{
    cout << "entre com o ID do cartao:";
    cin >> cardID;
}

void Catraca::operando()
{
    this->requisita_IP();
    cout << "1" ;
    this->servidor_funcionando();
    cout << "2" ;
    this->entrada_cardID();
    cout << "3" ;
    this->r = RestClient::get(this->IP + "user/id/card/" + this->cardID);

    cout << this->r.code << '\n' << this->r.body << '\n';
    this->buffer = r.body;
    this->j = json::parse(buffer);
    this->user_id = j["user_id"];
    cout << '\n' << "id do usuário:" << this->user_id << '\n';
    this->aux << this->user_id;
    this->r = RestClient::get(this->IP + "transaction/" + aux.str());
    this->buffer = this->r.body;
    this->j = json::parse(this->buffer);
    //cout << '\n' << this->buffer << '\n' << this->j << '\n';
    this->dentro.insere(new Node<List_trans>(new List_trans(j)));
    cout << '\n' << "saldo:" <<this->dentro.procura_username(j[0]["username"])->getInfo().atualiza_saldo() << '\n';
    /*if(this->dentro.procura_username(j[0]["username"]) != 0)
    {

    }
    else if(this->dentro.procura_username(j[0]["username"]) != 0)
    {

    }*/


}

#endif
