#include <iostream>
#include <stdexcept>
#include "interfaces.h"
#include "controladora.h"
#include "stubs.h"

using namespace std;

int main() {
    // Criar instâncias das classes controladoras.
    CntrInterfaceUsuario cntrInterfaceUsuario;
    CntrAAutenticacao cntrAAutenticacao;
    CntrIAConta cntrIAConta;
    CntrIAInvestimentos cntrIAInvestimentos;

    // Criar instâncias das classes de serviço.
    CntrISAutenticacao cntrISAutenticacao;
    CntrISC cntrISC;
    CntrISI cntrISI;

    // Configurar dependências das controladoras.
    cntrAAutenticacao.setCntrSAutenticacao(&cntrISAutenticacao);
    cntrIAConta.setCntrSConta(&cntrISC);
    cntrIAInvestimentos.setCntrISInvestimentos(&cntrISI);
    cntrIAInvestimentos.setCntrSConta(&cntrISC);

    // Configurar dependências da interface de usuário.
    cntrInterfaceUsuario.setCntrAAutenticacao(&cntrAAutenticacao);
    cntrInterfaceUsuario.setCntrIAConta(&cntrIAConta);
    cntrInterfaceUsuario.setCntrIAInvestimento(&cntrIAInvestimentos);

    // Interagir com o usuário.
    cntrInterfaceUsuario.interagirComUsuario();

    return 0;
}

