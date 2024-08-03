#ifndef CONTAINERS_H_INCLUDED
#define CONTAINERS_H_INCLUDED

#include "dominios.h"
#include "entidades.h"

#include <map>

using namespace std;

class ContainerConta{
private:
    map<string, Conta> container;
    static ContainerConta *instancia;
    ContainerConta(){};
public:
    static  ContainerConta* getInstancia();
    bool criar(Conta);
    bool excluir(Cpf);
    Conta visualizar(Conta*);
    bool existe(Conta*);
    bool editar(Conta);
};

class ContainerTitulos {
private:
    map<string, vector<Titulo>> container; // Usando CPF (string) como chave e Titulo como valor
    static ContainerTitulos* instancia;
    ContainerTitulos() {}; // Construtor privado para o Singleton

public:
    // Método para obter a instância única do ContainerTitulos
    static ContainerTitulos* getInstancia();

    bool criarTitulo(Cpf& cpf, Titulo& titulo);
    // Método para excluir um Titulo com base no CPF
    bool excluirTitulo(Cpf& cpf, CodigoDeTitulo& codigoTitulo);

    // Método para visualizar um Titulo com base no CPF
    vector<Titulo> visualizarTitulos(Cpf& cpf);

    // Método para verificar se um Titulo existe com base no CPF
    bool existe(CodigoDeTitulo& codigoDeTitulo);

    // Método para editar um Titulo existente
    bool editarTitulo(Cpf& cpf, Titulo& tituloAtualizado);
};

class ContainerPagamentos {
private:
    map<string, vector<Pagamento>> container; // Usando CPF (string) como chave e Titulo como valor
    static ContainerPagamentos* instancia;
    ContainerPagamentos() {}; // Construtor privado para o Singleton

public:
    // Método para obter a instância única do ContainerPagamentos
    static ContainerPagamentos* getInstancia();

    bool criarPagamento(CodigoDeTitulo& codigoDeTitulo, Pagamento& pagamento);

    // Método para excluir um Pagamento com base no CPF
    bool excluirPagamento(CodigoDePagamento& codigoDePagamento);
    bool excluirPagamentosPorTitulo(CodigoDeTitulo& codigoDeTitulo);

    // Método para visualizar um Pagamento com base no CodigoDeTitulo
    vector<Pagamento> visualizarPagamentos(CodigoDeTitulo& codigoDeTitulo);

    // Método para editar um Titulo existente
    bool editarPagamento(CodigoDeTitulo& codigoDeTitulo, Pagamento& pagamentoAtualizado);
};

#endif // CONTROLADORAS_H_INCLUDED
