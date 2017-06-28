#ifndef TRANSACTION_H
#define TRANSACTION_H


#include <string.h>
#include "restclient/restclient.h"
#include "jsonparser/json.hpp"
#include <iostream>

using namespace std;
using json = nlohmann::json;

/*{
    "cardID": "ABCD0002",
    "event": -1,
    "timestamp": "Tue, 20 Jun 2017 12:00:25 GMT",
    "user_id": 3,
    "username": "akkauam"
  }*/

class Transaction
{

    string cardID;
    double event;
    string timestamp;
    unsigned long int user_id;
    string username;

public:
    Transaction(string cardID, double event, string timestamp, unsigned long int user_id, string username);
    ~Transaction();
    string get_cardID();
    double get_event();
    string get_timestamp();
    unsigned long int get_user_id();
    string get_username();
    void show_transaction();

};



#endif // STUDEN_H
