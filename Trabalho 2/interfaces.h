#ifndef INTERFACES_H_INCLUDED
#define INTERFACES_H_INCLUDED

#include <iostream>
#include "dominios.h"
#include "entidades.h"

class ISAutenticacao;
class ISConta;
class ISInvestimentos;

/**
 * @class IAAutenticacao
 * @brief Interface para autentica&ccedil;&atilde;o.
 *
 * Define os m&eacute;todos necess&aacute;rios para autenticar um usu&aacute;rio e defini o controlador de autentica&ccedil;&atilde;o.
 */
class IAAutenticacao {
public:
    /**
     * @brief Autentica um usu&aacute;rio com base no CPF.
     * @param cpf Ponteiro para o CPF do usu&aacute;rio.
     * @return Verdadeiro se a autentica&ccedil;&atilde;o for bem-sucedida, falso caso contr&aacute;rio.
     */
    virtual bool autenticar(Cpf*) = 0;

    /**
     * @brief Define o controlador de autentica&ccedil;&atilde;o.
     * @param cntrSAutenticacao Ponteiro para o controlador de autentica&ccedil;&atilde;o.
     */
    virtual void setCntrSAutenticacao(ISAutenticacao *) = 0;

    virtual ~IAAutenticacao() {}
};

/**
 * @class IAConta
 * @brief Interface para opera&ccedil;&otilde;es relacionadas a contas.
 *
 * Define os m&eacute;todos para criar, executar(crud) e configurar o controlador de contas.
 */
class IAConta {
public:
    /**
     * @brief Cria uma nova conta.
     */
    virtual void criar() = 0;

    /**
     * @brief Executa opera&ccedil;&otilde;es associadas a uma conta(crud).
     * @param cpf CPF da conta a ser executada.
     */
    virtual bool executar(Cpf) = 0;

    /**
     * @brief Define o controlador de contas.
     * @param cntrSConta Ponteiro para o controlador de contas.
     */
    virtual void setCntrSConta(ISConta *) = 0;

    virtual ~IAConta() {}
};

/**
 * @class IAInvestimentos
 * @brief Interface para opera&ccedil;&otilde;es de investimentos.
 *
 * Define os m&eacute;todos para executar e criar t&iacute;tulos e pagamentos, al&eacute;m de configurar os controladores.
 */
class IAInvestimentos {
public:
    /**
     * @brief Executa opera&ccedil;&otilde;es de investimentos.
     * @param cpf CPF associado ao investimento.
     */
    virtual void executar(Cpf) = 0;

    /**
     * @brief Executa opera&ccedil;&otilde;es espec&iacute;ficas de um t&iacute;tulo(crud).
     * @param cpf CPF associado ao t&iacute;tulo.
     */
    virtual void executarTitulo(Cpf) = 0;

    /**
     * @brief Executa opera&ccedil;&otilde;es de pagamento.
     * @param cpf CPF associado ao pagamento.
     */
    virtual void executarPagamento(Cpf) = 0;

    /**
     * @brief Cria um novo t&iacute;tulo.
     * @param cpf Ponteiro para o CPF associado ao t&iacute;tulo(crud).
     * @return Verdadeiro se a cria&ccedil;&atilde;o for bem-sucedida, falso caso contr&aacute;rio.
     */
    virtual bool criarTitulo(Cpf*) = 0;

    /**
     * @brief Cria um novo pagamento.
     * @param cpf Ponteiro para o CPF associado ao pagamento.
     * @return Verdadeiro se a cria&ccedil;&atilde;o for bem-sucedida, falso caso contr&aacute;rio.
     */
    virtual bool criarPagamento(Cpf*) = 0;

    /**
     * @brief Define o controlador de investimentos.
     * @param cntrISInvestimentos Ponteiro para o controlador de investimentos.
     */
    virtual void setCntrISInvestimentos(ISInvestimentos*) = 0;

    /**
     * @brief Define o controlador de contas.
     * @param cntrSConta Ponteiro para o controlador de contas.
     */
    virtual void setCntrSConta(ISConta*) = 0;

    /**
     * @brief Busca uma conta com base no CPF.
     * @param cpf CPF da conta a ser buscada.
     * @return A conta associada ao CPF fornecido.
     */
    Conta buscarConta(Cpf cpf);

    virtual ~IAInvestimentos() {}
};

/**
 * @class ISAutenticacao
 * @brief Interface para autentica&ccedil;&atilde;o com senha.
 *
 * Define o m&eacute;todo para autenticar um usu&aacute;rio com CPF e senha.
 */
class ISAutenticacao {
public:
    /**
     * @brief Autentica um usu&aacute;rio com base no CPF e senha.
     * @param cpf CPF do usu&aacute;rio.
     * @param senha Senha do usu&aacute;rio.
     * @return Verdadeiro se a autentica&ccedil;&atilde;o for bem-sucedida, falso caso contr&aacute;rio.
     */
    virtual bool autenticar(Cpf, Senha) = 0;

    virtual ~ISAutenticacao() {}
};

/**
 * @class ISConta
 * @brief Interface para gerenciamento de contas.
 *
 * Define os m&eacute;todos para criar, visualizar, editar e excluir contas.
 */
class ISConta {
public:
    /**
     * @brief Cria uma nova conta.
     * @param conta Conta a ser criada.
     * @return Verdadeiro se a cria&ccedil;&atilde;o for bem-sucedida, falso caso contr&aacute;rio.
     */
    virtual bool criar(Conta) = 0;

    /**
     * @brief Visualiza os detalhes de uma conta.
     * @param conta Ponteiro para a conta a ser visualizada.
     * @return Verdadeiro se a visualiza&ccedil;&atilde;o for bem-sucedida, falso caso contr&aacute;rio.
     */
    virtual bool visualizar(Conta*) = 0;

    /**
     * @brief Edita os detalhes de uma conta.
     * @param conta Conta com as novas informa&ccedil;&otilde;es.
     * @return Verdadeiro se a edi&ccedil;&atilde;o for bem-sucedida, falso caso contr&aacute;rio.
     */
    virtual bool editar(Conta) = 0;

    /**
     * @brief Exclui uma conta com base no CPF.
     * @param cpf CPF da conta a ser exclu&iacute;da.
     * @return Verdadeiro se a exclus&atilde;o for bem-sucedida, falso caso contr&aacute;rio.
     */
    virtual bool excluir(Cpf) = 0;

    virtual ~ISConta() {}
};

/**
 * @class ISInvestimentos
 * @brief Interface para opera&ccedil;&otilde;es de investimentos.
 *
 * Define os m&eacute;todos para criar, visualizar, editar e excluir t&iacute;tulos e pagamentos.
 */
class ISInvestimentos {
public:
    /**
     * @brief Cria um novo t&iacute;tulo.
     * @param cpf CPF associado ao t&iacute;tulo.
     * @param titulo T&iacute;tulo a ser criado.
     * @return Verdadeiro se a cria&ccedil;&atilde;o for bem-sucedida, falso caso contr&aacute;rio.
     */
    virtual bool criarTitulo(Cpf, Titulo) = 0;

    /**
     * @brief Cria um novo pagamento.
     * @param codigoDeTitulo C&oacute;digo do t&iacute;tulo associado ao pagamento.
     * @param pagamento Pagamento a ser criado.
     * @return Verdadeiro se a cria&ccedil;&atilde;o for bem-sucedida, falso caso contr&aacute;rio.
     */
    virtual bool criarPagamento(CodigoDeTitulo, Pagamento) = 0;

    /**
     * @brief Visualiza os t&iacute;tulos associados a um CPF.
     * @param cpf CPF do usu&aacute;rio.
     * @return Vetor de t&iacute;tulos associados ao CPF.
     */
    virtual vector<Titulo> visualizarTitulos(Cpf cpf) = 0;

    /**
     * @brief Visualiza os pagamentos associados a um t&iacute;tulo.
     * @param codigoDeTitulo C&oacute;digo do t&iacute;tulo.
     * @return Vetor de pagamentos associados ao t&iacute;tulo.
     */
    virtual vector<Pagamento> visualizarPagamento(CodigoDeTitulo CodigoDeTitulo) = 0;

    /**
     * @brief Edita um t&iacute;tulo.
     * @param cpf CPF associado ao t&iacute;tulo.
     * @param titulo T&iacute;tulo com as novas informa&ccedil;&otilde;es editadas.
     * @return Verdadeiro se a edi&ccedil;&atilde;o for bem-sucedida, falso caso contr&aacute;rio.
     */
    virtual bool editarTitulo(Cpf, Titulo) = 0;

    /**
     * @brief Edita um pagamento.
     * @param codigoDeTitulo C&oacute;digo do t&iacute;tulo associado ao pagamento.
     * @param pagamento Pagamento com as novas informa&ccedil;&otilde;es editadas.
     * @return Verdadeiro se a edi&ccedil;&atilde;o for bem-sucedida, falso caso contr&aacute;rio.
     */
    virtual bool editarPagamento(CodigoDeTitulo, Pagamento) = 0;

    /**
     * @brief Exclui um t&iacute;tulo.
     * @param cpf CPF associado ao t&iacute;tulo.
     * @param codigoDeTitulo C&oacute;digo do t&iacute;tulo a ser exclu&iacute;do e todos pagamentos associados a ele.
     * @return Verdadeiro se a exclus&atilde;o for bem-sucedida, falso caso contr&aacute;rio.
     */
    virtual bool excluirTitulo(Cpf, CodigoDeTitulo) = 0;

    /**
     * @brief Exclui um pagamento.
     * @param codigoDePagamento C&oacute;digo do pagamento a ser exclu&iacute;do.
     * @return Verdadeiro se a exclus&atilde;o for bem-sucedida, falso caso contr&aacute;rio.
     */
    virtual bool excluirPagamento(CodigoDePagamento) = 0;

    virtual ~ISInvestimentos() {}
};

#endif
