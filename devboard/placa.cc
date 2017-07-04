#include <iostream>
#include "catraca.h"

#include "md5.h"

int main()
{
	
	/*string s = md5("151501624829504a00584f278a4cb26207c581860000");
	cout << s << endl;
	cout << s[0] << endl;
	return 1;
	*/

	
    Catraca* a = new Catraca;
    a->start();
    if (a->getStatus() != 1) {
        cout << "Não foi possível conectar com o servidor. Servidor Rodando?" << endl;
        return 0;
    } else {
        a->run();
    }

    return 1;
}