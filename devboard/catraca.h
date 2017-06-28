#ifndef CATrACA_H
#define CATrACA_H

#include <iostream>
#include <sstream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "restclient/restclient.h"
#include "jsonparser/json.hpp"
#include "list_trans.h"
#include "transaction.h"
#include "list_users.h"

using namespace std;
using json = nlohmann::json;


class Catraca
{
    List_users dentro;
    List_users fora;
    string IP;
    RestClient::Response r;
    string cardID;
    long int user_id;
    string buffer;
    json j;
    ostringstream aux;


public:
    void requisita_IP();
    void servidor_funcionando();
    void entrada_cardID();
    void operando();


};


#endif
