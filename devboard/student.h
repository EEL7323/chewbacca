#include <string>

using namespace std;

class Student 
{
    string cardID;
    int userID;
    int credito;
    string matricula;
    string salt;
    string password_hash;
    bool studentIn;
public:
    Student() { 
        credito = 0; 
        studentIn = false; 
        cardID = "";
        userID = 0;
        matricula = "";
        password_hash = "";
        salt = "";
    };
    string getCardID() { return cardID; };
    int getUserID() { return userID; };
    int getCredito() { return credito; };
    bool getStudentStatus() { return studentIn; };
    string getPassword() { return password_hash; };
    string getMatricula() { return matricula; };
    string getSalt() { return salt; };
    void setPassword(string s) { password_hash = s; };
    void setMatricula(string s) { matricula = s; };
    void setSalt(string s) { salt = s; };
    void setCardID(string s) { cardID = s; };
    void setUserId(int i) { userID = i; };
    void setCredito(int i) { credito = i; };
    void changeStudentStatus() { studentIn = !studentIn; }
};