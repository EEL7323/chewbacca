#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "restclient/restclient.h"
#include "jsonparser/json.hpp"
#include "list_trans.h"
#include "transaction.h"
#include "list_users.h"
#include "catraca.h"

using namespace std;
using json = nlohmann::json;

/*{
    "cardID": "ABCD0002",
    "event": -1,
    "timestamp": "Tue, 20 Jun 2017 12:00:25 GMT",
    "user_id": 3,
    "username": "akkauam"
  }*/

int main()
{
    //string buffer;
    //std::string str = "127.0.0.1:5000/";
    //json j;
    /*string cardID;
    double event;
    string timestamp;
    long int user_id;
    string username;
    int n =3;
    */
    //RestClient::Response r = RestClient::get(str);
    //cout << r.code;
    //buffer = r.body;
    //j = json::parse(buffer);
    //Transaction b(j[n]["cardID"], j[n]["event"], j[n]["timestamp"], j[n]["user_id"], j[n]["username"]);
    /*Transaction b(j[n]["cardID"], j[n]["event"], j[n]["timestamp"], j[n]["user_id"], j[n]["username"]);
    cardID = j[n]["cardID"];
    event = j[n]["event"];
    timestamp = j[n]["timestamp"];
    user_id = j[n]["user_id"];
    username = j[n]["username"];
    cout << buffer << '\n';
    cout << j[1]["username"] << '\n';

    std::cout << "cardID: " << cardID << '\n';
    std::cout << "event: " << event << '\n';
    std::cout << "timestemp: " << timestamp << '\n';
    std::cout << "user_id: " << user_id << '\n';
    std::cout << "username: " << username << '\n' << 'n';
    */

    //cout << buffer << '\n';
    /*
    List_users lista;
    lista.insere(new Node<List_trans>(new List_trans(j)));

    str = "127.0.0.1:5000/transaction/3";
    r = RestClient::get(str);
    cout << r.code;
    buffer = r.body;
    j = json::parse(buffer);
    lista.insere(new Node<List_trans>(new List_trans(j)));
    string nome = "vinicius";
    cout << '\n';
    lista.procura_username(nome)->getInfo().show_all_transactions();
    cout << '\n' << lista.procura_username(nome)->getInfo().atualiza_saldo() << '\n';
    //List_trans lista(j);


    //b.show_transaction();

    //cout << lista.atualiza_saldo() << '\n';

    //cout << j << '\n';
    //cout << j[5]["user_id"] << '\n';
    */
    Catraca a;

    //a.requisita_IP();
    //a.servidor_funcionando();
    a.operando();


    return 0;
}
