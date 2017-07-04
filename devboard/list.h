#include <string>
#include <thread>  
#include "nodo.h"
#include "student.h"

using namespace std;
enum TipoBusca {TipoCartao, TipoMatricula};
class List 
{
    Node<Student>* head;
	int contadorStudentIn;
public:
    List();
    ~List();
    Node<Student>* find(string cardID, TipoBusca tipo);
    void print();
    void append(Student* data);
    void apaga(Student* data);
    void updateContador();
    void incContador(Student* data);
    void decContador();
    int getContador();
};