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

	void run();
	void start();
	int getStatus();
	string getServerIP();
	int getServerPort();
	void setServerIP(string serverIP);
	void setServerPort(int serverPort);
	void upServerStudentCount(int contagem);
	//void setList(List* lista);


};

