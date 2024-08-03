#include <iostream>
#include <stdexcept>
#include "interfaces.h"
#include "controladora.h"
#include "stubs.h"

using namespace std;

int main() {
    // Criar inst�ncias das classes controladoras.
    CntrInterfaceUsuario cntrInterfaceUsuario;
    CntrAAutenticacao cntrAAutenticacao;
    CntrIAConta cntrIAConta;
    CntrIAInvestimentos cntrIAInvestimentos;

    // Criar inst�ncias das classes de servi�o.
    CntrISAutenticacao cntrISAutenticacao;
    CntrISC cntrISC;
    CntrISI cntrISI;

    // Configurar depend�ncias das controladoras.
    cntrAAutenticacao.setCntrSAutenticacao(&cntrISAutenticacao);
    cntrIAConta.setCntrSConta(&cntrISC);
    cntrIAInvestimentos.setCntrISInvestimentos(&cntrISI);
    cntrIAInvestimentos.setCntrSConta(&cntrISC);

    // Configurar depend�ncias da interface de usu�rio.
    cntrInterfaceUsuario.setCntrAAutenticacao(&cntrAAutenticacao);
    cntrInterfaceUsuario.setCntrIAConta(&cntrIAConta);
    cntrInterfaceUsuario.setCntrIAInvestimento(&cntrIAInvestimentos);

    // Interagir com o usu�rio.
    cntrInterfaceUsuario.interagirComUsuario();

    return 0;
}

