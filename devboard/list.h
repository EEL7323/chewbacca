#include <string>
#include <thread>  
#include "nodo.h"
#include "student.h"

using namespace std;
enum TipoBusca {TipoCartao, TipoMatricula};
class List 
{
    Node<Student>* head; //Inicio da lista
	int contadorStudentIn; //Quantidade de usuários com status "dentro do restaurante"
public:
    List();
    ~List();
    Node<Student>* find(string s, TipoBusca tipo); //Encontra o nodo com cardID|tipo especificado em s
    void print(); //Imprime informações da lista
    void append(Student* data); //Adiciona ou atualiza creditos de um usuario na lista
    void apaga(Student* data); //Apaga o nodo onde está data
    void updateContador(); //Atualiza o contador de usuarios dentro do restaurante lendo informações de cada usuário
    void incContador(Student* data); //Incrementa o contador de usuário atualizando o status do usuário
    void decContador(); //Decrementa o contador de usuário
    int getContador(); //Retorna a quantidade de usuários dentro do restaurante
};