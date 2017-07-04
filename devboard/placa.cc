#include <iostream>
#include "catraca.h"

int main()
{

    Catraca* a = new Catraca;
    a->start(); //Inicializa a placa/catraca
    if (a->getStatus() != 1) {
        cout << "Não foi possível conectar com o servidor. Servidor Rodando?" << endl;
        return 0;
    } else {
        a->run(); //Inicia o funcionamento da catraca
    }

    return 1;
}