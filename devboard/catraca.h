#include <string>
#include "list.h"

using namespace std;

class Catraca
{
	string serverIP;
	int serverPort;
	List* lista;
	int status;

public:
	Catraca();
	~Catraca();

	void run(); //Inicia o funcionamento da catraca
	void start(); //Inicializa a lista principal
	int getStatus(); //Retorna o status do funcionamento da placa, útil apenas no main
	string getServerIP(); 
	int getServerPort();
	void setServerIP(string serverIP);
	void setServerPort(int serverPort);
	void upServerStudentCount(int contagem);
	//void setList(List* lista);


};

