#include <string>

using namespace std;

class Student 
{
    string cardID; //identificador do cartão
    int userID; //identificador do usuario
    int credito; //quantidade total de créditos
    string matricula; //matricula do usuário
    string salt; //salt da senha
    string password_hash; //hash da senha original
    bool studentIn; //status do usuario, dentro ou fora do restaurante
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