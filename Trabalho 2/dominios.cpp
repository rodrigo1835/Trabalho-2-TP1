#include <iostream>
#include <cctype>
#include <string>
#include <cstdlib> 

#include "dominios.h"

using namespace std;

//-------------------(Classe-Nome)---------------------------------//
void Nome::validar(string nome) {
    if(nome.length() < 3 || nome.length() > 10)
        throw invalid_argument("Nome: Nome invalido.");
    
    if(!isupper(nome[0]))
        throw invalid_argument("Nome: O primeiro caractere de cada termo deve ser maiusculo");
    
    // Valida se tem algum caractere que não seja letra na string através do seu valor ascii.
    for(char caractere : nome) {
        int ascii = caractere;

        if(!((ascii >= 97 && ascii <= 122) || (ascii >= 65 && ascii <= 90)))
            throw invalid_argument("Nome: Caractere invalido");
    }
}

void Nome::setNome(string nome) {
    
    int posicao = nome.find(' '); // Encontra a posição do espaço caso seja um nome composto

    if(posicao == -1) { // Se a posicao é igual a -1 significa que não é um nome composto
        validar(nome);
        this ->nome = nome;

    } else {
        validar(nome.substr(0, posicao)); //Reparte a string até o primeiro nome
        validar(nome.substr(posicao + 1)); //Reparte a string para obter o sobrenome

        this->nome = nome.substr(0, posicao);
        this->sobrenome = nome.substr(posicao + 1); 
    }
}

//-------------------(Classe-Senha)---------------------------------//

bool Senha::sequenciaCrescente(string senha) {
    if(senha.length() <= 2)
        return false;

    for(int i = 0; i < senha.length() - 1; i++){
        if(senha[i] != senha[i + 1] + 1)
            return false;
    }

    return true;
}

bool Senha::sequenciaDecrescente(string senha) {
    if(senha.length() <= 2)
        return false;

    for(int i = 0; i < senha.length() - 1; i++){
        if(senha[i] != senha[i + 1] - 1)
            return false;
    }

    return true;
}

void Senha::validar(string senha) {
    if(senha.length() > LIMITE)
        throw invalid_argument("Senha: Limite máximo de caracteres atingidos.");

    if((sequenciaCrescente(senha) || sequenciaDecrescente(senha)))
        throw invalid_argument("Senha: Senha em ordem crescente ou decrescente.");
    
    if(senha[0] == '0')
        throw invalid_argument("Senha: O primeiro digito deve ser diferente de Zero");

    // Verifica se o caractere digitado na senha é um número através do seu valor na tabela ascii
    for(char numero : senha) {
        int ascii = numero;

        if(!(numero >= 48 && numero <= 57))
            throw invalid_argument("Senha: Senha com caracteres invalidos");
    }

    // Verifica se o número é repetido.
    vector<int> numeroRepetido(10,false); // Vetor de booleanos para verificação se algum número é repetido.
    for(char ascii : senha) {
        int numero = (ascii - '0');

        if(numeroRepetido[numero] == true)
            throw invalid_argument("Numero: Senha com números repetidos");
        
        numeroRepetido[numero] = true;
    }
}

void Senha::setSenha(string senha) {
    validar(senha);
    this->senha = senha;
}

//-------------------(Classe-Estado)---------------------------------//
const vector<string> Estado::ESTADOS_VALIDOS = {"Previsto", "Liquidado", "Inadimplente"};

void Estado::validar(string estado) {
    if(!(estado == ESTADOS_VALIDOS[0] || estado == ESTADOS_VALIDOS[1] ||estado == ESTADOS_VALIDOS[2]))
        throw invalid_argument("Estado: Estado invalido");
}

void Estado::setEstado(string estado) {
    validar(estado);
    this->estado = estado;
}

//-------------------(Classe-Percentual)---------------------------------//

void Percentual::validar(float percentual) {
    if(!(percentual >= 0 && percentual <= MAXIMO))
        throw invalid_argument("Percentual: Percentual inválido!");
}

void Percentual::setPercentual(float percentual) {
    validar(percentual);
    this->percentual = percentual;
}

void Percentual::setPercentual(string percentual) {
    throw invalid_argument("Percentual: Apenas número são aceitos.");
}

//-------------------(Classe-CodigoDePagamento)---------------------------------//

void CodigoDePagamento::validar(string codigoPagamento) {
    for(char numero : codigoPagamento) {
        int ascii = numero;

        if(!(numero >= 48 && numero <= 57))
            throw invalid_argument("CodigoDePagamento: código com caracteres invalidos");
    }
    
    if(codigoPagamento[0] == '0')
        throw invalid_argument("CódigoDePagamento: O primeiro digito do código tem que ser diferente de zero");
}

void CodigoDePagamento::setCodigoPagamento(string codigoPagamento) {
    validar(codigoPagamento);
    this->codigoPagamento = codigoPagamento;
}

//-------------------(Classe-Dinheiro)---------------------------------//
bool Dinheiro::verificarNumero(string dinheiro) {
    for(char numero : dinheiro) {
        if(!isdigit(numero))
            return false;
    }
    return true;
}

void Dinheiro::validar(string dinheiro) {
    if(!verificarNumero(dinheiro))
        throw invalid_argument("Dinheiro: O dinheiro contém caracteres não númericos.");

    int numeroConvertido = stol(dinheiro);
    if(numeroConvertido > DINHEIRO_MAXIMO)
        throw invalid_argument("Dinheiro: Limite máximo atingido");
    
}

void Dinheiro::setDinheiro(string dinheiro) {
    validar(dinheiro);
    this->dinheiro = dinheiro;
}

//-------------------(Classe-Cpf)---------------------------------//

void Cpf::validar(string cpf) {
    //Verifica a presença de números no cpf e remove caracteres especiais
    string cpfNumero;
    for(char digito : cpf) {
        if(isdigit(digito))
            cpfNumero += digito;
    }

    if(cpfNumero.length() != CPF_MAXIMO)
        throw invalid_argument("Cpf: Cpf ultrapassa ou é menor do que o esperado");
    
    vector<int> vetor_cpf(CPF_MAXIMO);
    for(int i = 0; i < 11; i++)
        vetor_cpf[i] = (cpfNumero[i] - '0');

    //Aqui começa a validação do cpf
    //Calcula o DV1
    int soma = 0;
    for(int i = 0; i < 9; i++)
        soma += vetor_cpf[i] * (10 - i);

    int dv1 = 11 - (soma % 11);
    if(dv1 >= 10)
        dv1 = 0;
    
    //Calcula o DV2
    soma = 0;
    for(int i = 0; i < 10; i++)
        soma += vetor_cpf[i] * (11 - i);
    
    int dv2 = 11 - (soma % 11);
    if(dv2 >= 10)
        dv2 = 0;

    if(!(vetor_cpf[9] == dv1 && vetor_cpf[10] == dv2))
        throw invalid_argument("Cpf: Cpf digitado é invalido");
}

void Cpf::setCpf(string cpf) {
    validar(cpf);
    this->cpf = cpf;
}

//-------------------(Classe-Setor)---------------------------------//
const vector<string> Setor::SETOR_VALIDOS = {"Agricultura","Construção civil","Energia","Finanças","Imobiliário","Papel e celulose","Pecuária", "Química e petroquímica","Metalurgia e siderurgia","Mineração"};

bool Setor::buscaSetor(string setor, vector<string> vetor) {
    for (string elemento : vetor) {
        if (elemento == setor)
            return true;
    }
    return false;
}

void Setor::validar(string setor) {
    if(!buscaSetor(setor, SETOR_VALIDOS))
        throw invalid_argument("Setor: setor inválido");
}

void Setor::setSetor(string setor) {
    validar(setor);
    this->setor = setor;
}

//-------------------(Classe-Data)---------------------------------//

void Data::validar(string data) {
    if (data.length() != 10 || data[2] != '-' || data[5] != '-') {
        throw std::invalid_argument("Data: Formato de data inválido. Use DD-MM-AAAA.");
    }

    int dia = stoi(data.substr(0, 2));
    int mes = stoi(data.substr(3, 2));
    int ano = stoi(data.substr(6, 4));

    if(!((dia >= 1 && dia <= 31) && (mes >= 1 && mes <= 12) && (ano >= 2000 && ano <= 2100)))
        throw invalid_argument("Data: Digito de data não obedece o padrão.");
}

void Data::setData(string data) {
    validar(data);
    this->data = data;
}

//-------------------(Classe-Data)---------------------------------//
const vector<string> CodigoDeTitulo::TITULOS_VALIDOS = {"CDB","CRA","CRI","LCA","LCI","DEB"};

bool CodigoDeTitulo::validarTitulo(string codigoTitulo) {
    for(string titulo : TITULOS_VALIDOS){
        if(titulo == codigoTitulo)
            return true;
    }

    return false;
}

void CodigoDeTitulo::validar(string codigoTitulo) {
    if(!validarTitulo(codigoTitulo.substr(0,3)))
        throw invalid_argument("CodigoDeTitulo: Código de titulo inválido");

    for(char numeroAscii : codigoTitulo.substr(4, codigoTitulo.length())){
        if(!((numeroAscii >= 48 && numeroAscii <= 57) || (numeroAscii >= 65 && numeroAscii <= 90)))
            throw invalid_argument("CodigoDeTitulo: caractere digitado não é um intervalo de [A,Z] ou [0,9]");
    }
}

void CodigoDeTitulo::setCodigoTitulo(string codigoTitulo) {
    validar(codigoTitulo);
    this->codigoTitulo = codigoTitulo;
}