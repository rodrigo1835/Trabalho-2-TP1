#ifndef DOMINIOS_H_INCLUDED
#define DOMINIOS_H_INCLUDED

#include <iostream>
#include <vector>
#include <string>

using namespace std;

/**@class Nome
*@brief Classe armazena um nome no formato string.
*@author Rodrigo - 222026546
*
*@details
*O limite s&oacute; &eacute; v&aacute;lido para uma string que seja maior que 3 menor que 10.
*
*/

class Nome {
    private:
        string nome;
        string sobrenome = ""; // Atribui uma string vazia caso o nome não seja composto
        void validar(string);

    public:
        /**
         *@brief Define um nome
         *
         *Armazena um nome. O nome deve ser maior que 3 menor 10.
         *
         *@param string representa o nome a ser armazenado.
         *
         *@throw invalid_argument caso n&atilde;o seja nenhum dos valores v&aacute;lido.
         *
        */
        void setNome(string);
        /**
         * @brief Retorna o nome armazenado.
         *
         *
        */
        string getNome() const;
};
/**
 * @return string representando o nome + sobrenome caso haja.
*/
inline string Nome::getNome() const{
    return nome + " " + sobrenome;
}


/**@class Senha
*@brief Classe armazena uma senha no formato string.
*@author Rodrigo - 222026546
*
*@details
*O limite s&oacute; &eacute; v&aacute;lido para uma string que atendas a seguintes regras:
*n&aacute;o a digitos repetidos, a senhao n&aacute;o pode *est&aacute em ordem crescente,decreste e o primeiro digito *diferente de zero.
*
*/
class Senha {
    private:
        static const int LIMITE = 10;
        string senha;
        bool sequenciaCrescente(string);
        bool sequenciaDecrescente(string);
        void validar(string);

    public:
           /**
         *@brief Define uma senha
         *
         *Armazena uma senha. Que deve obdecer as regras que est&aacute descrita no detalhe da Classe .
         *
         *@param string representa a senha a ser armazenado.
         *
         *@throw invalid_argument caso n&atilde;o seja nenhum dos valores v&aacute;lido.
         *
        */
        void setSenha(string);
        /**
         * @brief Retorna a senha armazenada.
        */
        string getSenha() const;
};

/**
 * @return string representando a senha.
*/
inline string Senha::getSenha() const{
    return senha;
}

/**@class Estado
*@brief Classe armazena um Estado no formato string.
*@author Rodrigo - 222026546
*
*@details
*A classe armazena um vetor no formato de string de estados j&aacute conhecidos.
*
*/

class Estado {
    private:
        string estado;
        static const vector<string> ESTADOS_VALIDOS;
        void validar(string);
    public:
        /**
         *@brief Define um estado
         *
         *Armazena um estado. Que deve ser algum desses descritos = {"Previsto,Liquidado,Inadimplente"}.
         *
         *@param string representa um estado a ser armazenado.
         *
         *@throw invalid_argument caso n&atilde;o seja nenhum dos valores v&aacute;lido.
         *
        */
        void setEstado(string);
        /**
         * @brief Retorna o estado armazenado.
        */
        string getEstado() const;
};
/**
 * @return string representando o estado.
*/
inline string Estado::getEstado() const{
    return estado;
}

/**@class Percentual
*@brief Classe armazena um percentual no formato de string.
*@author Rodrigo - 222026546
*
*@details
*Os valores lidos são guardados na classe em formato de porcentagem, Ex: 100%.
*
*/
class Percentual {
    private:
        float percentual = 0.0;
        static const int MAXIMO = 100;
        void validar(float);
    public:
        /**
         *@brief Define um percentual.
         *
         *Armazena um percentual em formato float. Que deve ser maior ou igual a 0 menor ou igual a 100.
         *
         *@param float representa um percentual a ser armazenado.
         *
         *@throw invalid_argument caso n&atilde;o seja nenhum dos valores v&aacute;lido.
         *
        */
        void setPercentual(float);
        void setPercentual(string);
        /**
         * @brief Retorna o estado armazenado.
        */
        float getPercentual() const;
};
/**
 * @return float representando o percentual.
*/
inline float Percentual::getPercentual() const{
    return percentual;
}

/**@class CodigoDePagamento
*@brief Classe armazena um c&oacute;digo no formato de string.
*@author Rodrigo - 222026546
*
*@details
*Essa classe guarda valores de código de pagamentos que seguem uma l&oacute;gica que est&aacute descrita no setCodigoPagamento.
*
*/

class CodigoDePagamento {
    private:

        void validar(string);
    public:
        string codigoPagamento;
        /**
         *@brief Define um codigo de pagamento.
         *
         *Armazena um codigo em formato de string. Que deve ser no Formato XXXXXXXX. X &eacute d&iacute;gito (0-9) Primeiro dígito &eacute diferente de zero (1-9)
         *
         *@param string representa um codigo de pagamento a ser armazenado.
         *
         *@throw invalid_argument caso n&atilde;o seja nenhum dos valores v&aacute;lido.
         *
        */
        void setCodigoPagamento(string);
        /**
         * @brief Retorna o codigo de pagamento armazenado.
        */
        string getCodigoPagamento() const;
};
/**
 * @return string representando o codigo de pagamento.
*/
inline string CodigoDePagamento::getCodigoPagamento() const{
    return codigoPagamento;
}

/**@class Dinheiro
*@brief Classe armazena um valor no formato de string.
*@author Rodrigo - 222026546
*
*@details
*Os valor armazenado nessa classe representa Dinheiro
*
*/

class Dinheiro {
    private:
        string dinheiro;
        static const int DINHEIRO_MAXIMO = 100000000;
        void validar(string);
        bool verificarNumero(string);

    public:
        /**
         *@brief Define um valor para o dinheiro.
         *
         *Armazena um valor em formato de string. Que deve ser uma Valor 0 a 1.000.000,00.
         *
         *@param string representa um valor de dinheiro a ser armazenado.
         *
         *@throw invalid_argument caso n&atilde;o seja nenhum dos valores v&aacute;lido.
         *
        */
        void setDinheiro(string);
        /**
         * @brief Retorna o valor do dinheiro, EX: 100000.
        */
        int getDinheiro() const;
};
/**
 * @return string representando o valor do dinheiro.
*/
inline int Dinheiro::getDinheiro() const{
    return stoi(dinheiro);
}


/**@class Cpf
*@brief Classe armazena um valor no formato de string.
*@author Rodrigo - 222026546
*
*@details
*Os valor armazenado nessa classe representa cpf validado pelo sistema oficial de verificagem. para testar sem usar cpf reais use (123.456.789-09).
*
*/

class Cpf {
    private:
        string cpf;
        static const int CPF_MAXIMO = 11;
        void validar(string);
    public:
        /**
         *@brief Define um valor para o cpf.
         *
         *Armazena um cpf em formato de string. Que deve ser Formato XXX.XXX.XXX-CC
          X - Dígito (0-9), Pontos usados para separar sequências de 3 d&iacute;gitos
          H&iacute;fen usado para separar sequencias de d&iacute;gitos de caracteres de validação
          CC - Caracteres de validação calculados segundo algoritmo de validação de CPF.
         *
         *@param string representa um cpf a ser armazenado.
         *
         *@throw invalid_argument caso n&atilde;o seja nenhum dos valores v&aacute;lido.
         *
        */
        void setCpf(string);
        /**
         * @brief Retorna o valor do cpf.
        */
        string getCpf() const;
};
/**
 * @return string representando o valor do cpf.
*/
inline string Cpf::getCpf() const{
    return cpf;
}

/**@class Setor
*@brief Classe armazena um setor.
*@author Rodrigo - 222026546
*
*@details
*Os valores armazenado nessa classe são do tipo vetor de strings.
*
*/
class Setor {
    private:
        string setor;
        bool buscaSetor(string,vector<string>);
        void validar(string);

    public:
        static const vector<string> SETOR_VALIDOS;
        /**
         *@brief Define um valor para o setor.
         *
         *Armazena um setor caso ele seja valido, aqui estão todos os setores validos =
            {Agricultura
            Construção civil
            Energia
            Finanças
            Imobiliário
            Papel e celulose
            Pecuária
            Química e petroquímica
            Metalurgia e siderurgia
            Mineração}
         *
         *@param string representa um setor a ser armazenado.
         *
         *@throw invalid_argument caso n&atilde;o seja nenhum dos valores v&aacute;lido.
         *
        */
        void setSetor(string);
        /**
         * @brief Retorna o valor do setor.
        */
        string getSetor() const;
};
/**
 * @return string representando o valor do setor.
*/
inline string Setor::getSetor() const{
    return setor;
}

/**@class Data
*@brief Classe armazena uma data.
*@author Rodrigo - 222026546
*
*@details
*Os valores armazenado nessa classe são do tipo string que tem o seguinte formato DD-MM-AAAA.
*
*/

class Data {
    private:
        string data;
        void validar(string);

    public:
        /**
         *@brief Define um valor para a Data.
         *
         *Armazena uma data que obedece as seguintes regras Formato DD-MM-AAAA
          DD - 00 a 31
          MM - 01 a 12
          AAAA - 2000 a 2100
          Hífens usados para separar dias, mêses e anos
          Levar em consideração anos bissextos
         *
         *@param string representa uma data a ser armazenada.
         *
         *@throw invalid_argument caso n&atilde;o seja nenhum dos valores v&aacute;lido.
         *
        */
        void setData(string);
        /**
         * @brief Retorna o valor da data.
        */
        string getData() const;
};
/**
 * @return string representando o valor da data.
*/
inline string Data::getData() const{
    return data;
}

/**@class CodigoDeTitulo
*@brief Classe armazena um codigo de titulo.
*@author Rodrigo - 222026546
*
*@details
*Os valores armazenado nessa classe são do tipo string e todos os c&oacute;digos tem os primeiros 3 digitos relacionados ao tipo de investimento. Ex: DEBXXXXXXXX.
*
*/
class CodigoDeTitulo {
    private:
        string codigoTitulo;
        bool validarTitulo(string);
        void validar(string);

    public:
        static const vector<string> TITULOS_VALIDOS;
        /**
         *@brief Define um valor para o codigo de titulo.
         *
         *Armazena um codigo de titulo que obdece as seguintes regras:
          CDBXXXXXXXX
          CRAXXXXXXXX
          CRIXXXXXXXX
          LCAXXXXXXXX
          LCIXXXXXXXX
          DEBXXXXXXXX
          X - Letra maiúscula (A-Z) ou d&iacute;gito (0-9)
         *
         *@param string representa um codigo de tituli a ser armazenado.
         *
         *@throw invalid_argument caso n&atilde;o seja nenhum dos valores v&aacute;lido.
         *
        */
        void setCodigoTitulo(string);
        /**
         * @brief Retorna o valor do codigo de titulo.
        */
        string getCodigoTitulo() const;
};

/**
 * @return string representando o valor do codigo de titulo.
*/
inline string CodigoDeTitulo::getCodigoTitulo() const{
    return codigoTitulo;
}

#endif // DOMINIOS_H_INCLUDED
