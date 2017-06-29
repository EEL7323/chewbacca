#include <string>

using namespace std;

class Student 
{
    string cardID;
    int userID;
    int credito;
    bool studentIn;
public:
    Student() { 
        credito = 0; 
        studentIn = false; 
        cardID = "";
        userID = 0;
    };
    string getCardID() { return cardID; };
    int getUserID() { return userID; };
    int getCredito() { return credito; };
    bool getStudentStatus() { return studentIn; };
    void setCardID(string s) { cardID = s; };
    void setUserId(int i) { userID = i; };
    void setCredito(int i) { credito = i; };
    void changeStudentStatus() { studentIn = !studentIn; }
};