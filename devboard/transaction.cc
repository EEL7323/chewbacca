#ifndef TRANSACTION_CPP
#define TRANSACTION_CPP
#include "transaction.h"

Transaction::Transaction(string cardID, double event, string timestamp, unsigned long int user_id, string username)
{
    this->cardID = cardID;
    this->event = event;
    this->timestamp = timestamp;
    this->user_id = user_id;
    this->username = username;
}
Transaction::~Transaction()
{

}

string Transaction::get_cardID()
{
    return this->cardID;
}
double Transaction::get_event()
{
    return this->event;
}
string Transaction::get_timestamp()
{
    return this->timestamp;
}
unsigned long int Transaction::get_user_id()
{
    return this->user_id;
}
string Transaction::get_username()
{
    return this->username;
}
void Transaction::show_transaction()
{
    std::cout << "cardID: " << this->cardID << '\n';
    std::cout << "event: " << this->event << '\n';
    std::cout << "timestamp: " << this->timestamp << '\n';
    std::cout << "user_id: " << this->user_id << '\n';
    std::cout << "username: " << this->username << '\n' << '\n';
}
#endif
