#ifndef STUBS_H_INCLUDED
#define STUBS_H_INCLUDED

#include "interfaces.h"

#include <stdexcept>
#include <iostream>
#include <typeinfo>

using namespace std;

// -------------------------------------------------------------------------------------------
// Declara��o de classe stub.
//
// Classe StubLNAutenticacao implementa a interface ILNAutenticacao.

class StubISAutenticacao:public ISAutenticacao{

private:

    // Defini��es de valores a serem usados como gatilhos para notifica��es de erros.

    static const string TRIGGER_FALHA;
    static const string TRIGGER_ERRO_SISTEMA;

public:

    // Declara��o de m�todo previsto em interface.

    bool autenticar(const Cpf, const Senha);
};


#endif // STUBS_H_INCLUDED
