#ifndef CONTROLADORAS_H_INCLUDED
#define CONTROLADORAS_H_INCLUDED

#include "interfaces.h"
#include "dominios.h"
#include "entidades.h"

#include <iostream>

class CntrInterfaceUsuario {
private:
    IAAutenticacao *cntrAAutenticacao;
    IAConta *cntrIAConta;
    IAInvestimentos *cntrIAInvestimentos;

public:
    void interagirComUsuario();
    void setCntrAAutenticacao(IAAutenticacao*);
    void setCntrIAConta(IAConta*);
    void setCntrIAInvestimento(IAInvestimentos*);
};

class CntrAAutenticacao:public IAAutenticacao {
private:
    ISAutenticacao *cntrSAutenticacao;

public:
    bool autenticar(Cpf*);
    void setCntrSAutenticacao(ISAutenticacao *);
};

void inline CntrAAutenticacao::setCntrSAutenticacao(ISAutenticacao *cntr){
        this->cntrSAutenticacao = cntr;
}

class CntrIAConta:public IAConta{
private:
    ISConta *cntrSConta;

public:
    void criar();
    bool executar(Cpf);
    void setCntrSConta(ISConta*);
};

inline void CntrIAConta::setCntrSConta(ISConta *cntrSC){
    this -> cntrSConta = cntrSC;
}

class CntrIAInvestimentos:public IAInvestimentos {
private:
    ISInvestimentos *cntrSInvestimentos;
    ISConta *cntrSConta;

public:

    void executar(Cpf);
    void executarTitulo(Cpf);
    void executarPagamento(Cpf);

    bool criarTitulo(Cpf*);
    bool criarPagamento(Cpf*);

    Conta buscarConta(Cpf cpf);

    void setCntrISInvestimentos(ISInvestimentos *);
    void setCntrSConta(ISConta*);
};

inline void CntrIAInvestimentos::setCntrISInvestimentos(ISInvestimentos *cntrSInv) {
    this->cntrSInvestimentos = cntrSInv;
}

//  CONTROLADORAS-SERVICOS
class CntrISAutenticacao:public ISAutenticacao {
    public:
        bool autenticar(Cpf, Senha);
};

class CntrISC:public ISConta {
public:
    bool criar(Conta);
    bool visualizar(Conta*);
    bool editar(Conta);
    bool excluir(Cpf);
};

class CntrISI:public ISInvestimentos {
public:
    bool criarTitulo(Cpf, Titulo);
    bool criarPagamento(CodigoDeTitulo, Pagamento);

    vector<Titulo> visualizarTitulos(Cpf cpf);
    vector<Pagamento> visualizarPagamento(CodigoDeTitulo codigoDeTitulo);

    bool editarTitulo(Cpf, Titulo);
    bool editarPagamento(CodigoDeTitulo, Pagamento);

    bool excluirTitulo(Cpf, CodigoDeTitulo);
    bool excluirPagamento(CodigoDePagamento);
};

#endif // CONTROLADORAS_H_INCLUDED
