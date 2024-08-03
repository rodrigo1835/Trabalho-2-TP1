#ifndef ENTIDADES_H_INCLUDED
#define ENTIDADES_H_INCLUDED

#include "dominios.h"
#include <string>

//Todas as classes Entidades foram desenvolvidas por: Rodrigo Reis - 222026546

using namespace std;

/**
 * @class Conta
 * @brief Classe Entidade armazena uma conta
 * @details Os valores armazenados nessa classe são objetos das classes de domínio: Cpf, Nome e Senha.
 */
class Conta {
private:
    Cpf cpf;     ///< CPF associado à conta
    Nome nome;   ///< Nome associado à conta
    Senha senha; ///< Senha associada à conta

public:
    /**
     * @brief Define o CPF da conta.
     * @param cpf CPF a ser definido.
     */
    void setCpf(const Cpf&);

    /**
     * @brief Obtém o CPF da conta.
     * @return CPF da conta.
     */
    Cpf getCpf() const;

    /**
     * @brief Define o nome da conta.
     * @param nome Nome a ser definido.
     */
    void setNome(const Nome&);

    /**
     * @brief Obtém o nome da conta.
     * @return Nome da conta.
     */
    Nome getNome() const;

    /**
     * @brief Define a senha da conta.
     * @param senha Senha a ser definida.
     */
    void setSenha(const Senha&);

    /**
     * @brief Obtém a senha da conta.
     * @return Senha da conta.
     */
    Senha getSenha() const;
};

inline void Conta::setCpf(const Cpf& cpf) {
    this->cpf = cpf;
}

inline Cpf Conta::getCpf() const {
    return cpf;
}

inline void Conta::setNome(const Nome& nome) {
    this->nome = nome;
}

inline Nome Conta::getNome() const {
    return nome;
}

inline void Conta::setSenha(const Senha& senha) {
    this->senha = senha;
}

inline Senha Conta::getSenha() const {
    return senha;
}

//-------------------------------------------------------//

/**
 * @class Titulo
 * @brief Classe Entidade armazena um título.
 * @details Os valores armazenados nessa classe são objetos das classes de domínio: CodigoDeTitulo, Nome, Setor, Data e Dinheiro.
 */
class Titulo {
private:

    Nome emissor;          ///< Nome do emissor do título
    Setor setor;           ///< Setor do título
    Data emissao;          ///< Data de emissão do título
    Data vencimento;       ///< Data de vencimento do título
    Dinheiro valor;        ///< Valor do título

public:
    CodigoDeTitulo codigo; ///< Código do título
    /**
     * @brief Define o código do título.
     * @param codigo Código a ser definido.
     */
    void setCodigo(const CodigoDeTitulo&);

    /**
     * @brief Obtém o código do título.
     * @return Código do título.
     */
    CodigoDeTitulo getCodigo() const;

    /**
     * @brief Define o emissor do título.
     * @param emissor Nome do emissor a ser definido.
     */
    void setEmissor(const Nome&);

    /**
     * @brief Obtém o emissor do título.
     * @return Nome do emissor do título.
     */
    Nome getEmissor() const;

    /**
     * @brief Define o setor do título.
     * @param setor Setor a ser definido.
     */
    void setSetor(const Setor&);

    /**
     * @brief Obtém o setor do título.
     * @return Setor do título.
     */
    Setor getSetor() const;

    /**
     * @brief Define a data de emissão do título.
     * @param emissao Data de emissão a ser definida.
     */
    void setEmissao(const Data&);

    /**
     * @brief Obtém a data de emissão do título.
     * @return Data de emissão do título.
     */
    Data getEmissao() const;

    /**
     * @brief Define a data de vencimento do título.
     * @param vencimento Data de vencimento a ser definida.
     */
    void setVencimento(const Data&);

    /**
     * @brief Obtém a data de vencimento do título.
     * @return Data de vencimento do título.
     */
    Data getVencimento() const;

    /**
     * @brief Define o valor do título.
     * @param valor Valor a ser definido.
     */
    void setValor(const Dinheiro&);

    /**
     * @brief Obtém o valor do título.
     * @return Valor do título.
     */
    Dinheiro getValor() const;
};

inline void Titulo::setCodigo(const CodigoDeTitulo& codigo) {
    this->codigo = codigo;
}

inline CodigoDeTitulo Titulo::getCodigo() const {
    return codigo;
}

inline void Titulo::setEmissor(const Nome& emissor) {
    this->emissor = emissor;
}

inline Nome Titulo::getEmissor() const {
    return emissor;
}

inline void Titulo::setSetor(const Setor& setor) {
    this->setor = setor;
}

inline Setor Titulo::getSetor() const {
    return setor;
}

inline void Titulo::setEmissao(const Data& emissao) {
    this->emissao = emissao;
}

inline Data Titulo::getEmissao() const {
    return emissao;
}

inline void Titulo::setVencimento(const Data& vencimento) {
    this->vencimento = vencimento;
}

inline Data Titulo::getVencimento() const {
    return vencimento;
}

inline void Titulo::setValor(const Dinheiro& valor) {
    this->valor = valor;
}

inline Dinheiro Titulo::getValor() const {
    return valor;
}

//-----------------(Entidade-Pagamento)--------------------------//

/**
 * @class Pagamento
 * @brief Classe Entidade armazena um pagamento.
 * @details Os valores armazenados nessa classe são objetos das classes de domínio: CodigoDePagamento, Data, Percentual e Estado.
 */
class Pagamento {
private:
    Data data;                ///< Data do pagamento
    Percentual percentual;    ///< Percentual do pagamento
    Estado estado;            ///< Estado do pagamento

public:
    CodigoDePagamento codigo; ///< Código do pagamento
    /**
     * @brief Define o código do pagamento.
     * @param codigo Código a ser definido.
     */
    void setCodigo(const CodigoDePagamento&);

    /**
     * @brief Obtém o código do pagamento.
     * @return Código do pagamento.
     */
    CodigoDePagamento getCodigo() const;

    /**
     * @brief Define a data do pagamento.
     * @param data Data a ser definida.
     */
    void setData(const Data&);

    /**
     * @brief Obtém a data do pagamento.
     * @return Data do pagamento.
     */
    Data getData() const;

    /**
     * @brief Define o percentual do pagamento.
     * @param percentual Percentual a ser definido.
     */
    void setPercentual(const Percentual&);

    /**
     * @brief Obtém o percentual do pagamento.
     * @return Percentual do pagamento.
     */
    Percentual getPercentual() const;

    /**
     * @brief Define o estado do pagamento.
     * @param estado Estado a ser definido.
     */
    void setEstado(const Estado&);

    /**
     * @brief Obtém o estado do pagamento.
     * @return Estado do pagamento.
     */
    Estado getEstado() const;
};

inline void Pagamento::setCodigo(const CodigoDePagamento& codigo) {
    this->codigo = codigo;
}

inline CodigoDePagamento Pagamento::getCodigo() const {
    return codigo;
}

inline void Pagamento::setData(const Data& data) {
    this->data = data;
}

inline Data Pagamento::getData() const {
    return data;
}

inline void Pagamento::setPercentual(const Percentual& percentual) {
    this->percentual = percentual;
}

inline Percentual Pagamento::getPercentual() const {
    return percentual;
}

inline void Pagamento::setEstado(const Estado& estado) {
    this->estado = estado;
}

inline Estado Pagamento::getEstado() const {
    return estado;
}

#endif // ENTIDADES_H_INCLUDED
