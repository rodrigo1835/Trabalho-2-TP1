#include "stubs.h"

using namespace std;
// Definição de constantes
const string StubISAutenticacao::TRIGGER_FALHA = "00000000000";
const string StubISAutenticacao::TRIGGER_ERRO_SISTEMA = "99999999999";

// Implementação de métodos de StubISAutenticacao
bool StubISAutenticacao::autenticar(Cpf cpf, Senha senha) {
    cout << endl << "StubISAutenticacao::autenticar" << endl;
    cout << "Cpf = " << cpf.getCpf() << endl;
    cout << "Senha = " << senha.getSenha() << endl;

    if(cpf.getCpf() == TRIGGER_FALHA) {
        return false;
    } else if(cpf.getCpf() == TRIGGER_ERRO_SISTEMA) {
        throw runtime_error("Erro de sistema");
    }

    return true;
}
