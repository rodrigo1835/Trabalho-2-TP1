 #include "controladora.h"
 #include "dominios.h"
 #include "entidades.h"
 #include "containers.h"

 #include <iostream>
 #include <cstdlib>
 #include <ctime>
 #include <string>
 #include <sstream>
 #include <iomanip>
 #include <random>
// ---------------------------------------------------------------------------------
using namespace std;

const string RESET = "\033[0m";
const string RED = "\033[31m";
const string GREEN = "\033[32m";

// Configura o gerador de números aleatórios para o código do titulo e pagamentos.
random_device rd;
mt19937 gen(rd());
uniform_int_distribution<> distrib(100000, 999999);

// Função para limpar o terminal tanto para windows e linux.
void limparTerminal() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void CntrInterfaceUsuario::interagirComUsuario() {
    while(true) {
        int opcao;
        cout << "Seja bem vindo ao sistema de Titulos/Pagamentos" << endl;
        cout << "Escolha uma opção abaixo:" << endl << endl;
        cout << "1. Autenticar" << endl;
        cout << "2. Criar nova conta" << endl;
        cout << "3. Sair" << endl;
        cout << "Sua opção: ";
        cin >> opcao;

        switch(opcao) {
            case 1: {
                limparTerminal();
                Cpf cpf;
                bool autenticado = cntrAAutenticacao->autenticar(&cpf);

                if (autenticado) {
                    limparTerminal();
                    cout << GREEN << "Autenticação realizada com sucesso para o cpf: " << RESET << cpf.getCpf() << endl;
                    cout << "Pressione Enter para continuar" << endl;
                    cin.ignore();
                    cin.get();

                    bool tela = true;

                    while(tela) {
                        limparTerminal();
                        cout << "Escolha qual serviço deseja: " << endl << endl;
                        cout << "1. Acessar Conta." << endl;
                        cout << "2. Acessar Investimentos" << endl;
                        cout << "3. Voltar para a tela inicial." << endl;
                        cout << "Sua opção: ";
                        cin >> opcao;

                        switch(opcao) {
                            case 1: {
                                try {
                                    if(cntrIAConta->executar(cpf)) {
                                        // Se a conta foi excluída retorna ao menu principal
                                        tela = false;
                                    }
                                } catch(const invalid_argument) {
                                    cout << RED << "Erro ao executar conta!" << RESET;
                                    tela = false;
                                }
                                break;
                            }

                            case 2: {
                                try {
                                    cntrIAInvestimentos->executar(cpf);
                                } catch(const invalid_argument) {
                                    cout << RED << "Erro ao executar investimento!" << RESET;
                                    tela = false;
                                }
                                break;
                            }

                            case 3: {
                                tela = false;
                                limparTerminal();
                                break;
                            }

                            default: {
                                limparTerminal();
                                cout << RED << "Opção Inválida" << RESET << endl;
                                cout << "Pressione Enter para continuar" << endl;
                                cin.ignore();
                                cin.get();
                                break;
                            }
                        }
                    }
                } else {
                    limparTerminal();
                    cout << RED << "Autenticação falhou. Tente novamente." << RESET << endl;
                }
                break;
            }

            case 2: {
                limparTerminal();
                cntrIAConta->criar();
                break;
            }

            case 3: {
                return;
            }

            default: {
                limparTerminal();
                cout << RED << "Opção Inválida" << RESET << endl;
                cout << "Pressione Enter para continuar" << endl;
                cin.ignore();
                cin.get();
                break;
            }
        }
    }
}


void CntrInterfaceUsuario::setCntrAAutenticacao(IAAutenticacao *cntr) {
    this->cntrAAutenticacao = cntr;
}

void CntrInterfaceUsuario::setCntrIAConta(IAConta *cntr) {
    this->cntrIAConta = cntr;
}

void CntrInterfaceUsuario::setCntrIAInvestimento(IAInvestimentos *cntr) {
    this->cntrIAInvestimentos = cntr;
}

void CntrIAInvestimentos::setCntrSConta(ISConta *cntrSC) {
    this->cntrSConta = cntrSC;
}

bool CntrAAutenticacao::autenticar(Cpf *cpf) {
    Senha senha;
    string entrada;

    cout << "Autenticacao de usuario." << endl << endl;

    try {
        cout << "Digite o Cpf : ";
        cin >> entrada;
        cpf->setCpf(entrada);
        cout << "Digite a senha : ";
        cin >> entrada;
        senha.setSenha(entrada);
    }
    catch (const invalid_argument &exp) {
        cout << endl << RED << "Dado em formato incorreto." << RESET << endl;
    }

    bool resultado = cntrSAutenticacao->autenticar(*cpf, senha);

    return resultado;
}

void CntrIAConta::criar() {

    string nomeEntrada,cpfEntrada,senhaEntrada;

    Nome nome;
    Cpf cpf;
    Senha senha;

    cout << "Preencha os campos a seguir:" << endl;
    cout << "Seu Nome: ";
    cin.ignore();
    getline(cin, nomeEntrada);
    cout << "Seu Cpf: ";
    cin >> cpfEntrada;
    cout << "Sua senha: ";
    cin >> senhaEntrada;
    cout << endl;

    limparTerminal();

    try {
        nome.setNome(nomeEntrada);
        cpf.setCpf(cpfEntrada);
        senha.setSenha(senhaEntrada);
    } catch(invalid_argument &exp) {
        cout << RED << "Dados em formato incorreto. Tente novamente!" << RESET << endl;
        return;
    }

    Conta conta;

    conta.setNome(nome);
    conta.setCpf(cpf);
    conta.setSenha(senha);

    try {
        cntrSConta->criar(conta);
        cout << GREEN << "Sucesso ao criar a Conta!" << RESET << endl;
    } catch(invalid_argument &exp) {
        cout << RED << "Falha ao criar a Conta" << RESET << endl;
    }

}

bool CntrIAConta::executar(Cpf cpf) {
    int opcao;
    bool tela = true;
    char voltar[] = "Aperte Enter para voltar.";

    while(tela) {
        limparTerminal();
        cout << "Selecione algum serviço de conta abaixo: " << endl;
        cout << "1. Visualizar dados pessoais. " << endl;
        cout << "2. Editar dados pessoais. " << endl;
        cout << "3. Eliminar Conta. " << endl;
        cout << "4. Retornar." << endl;
        cout << "Sua opção: ";

        cin >> opcao;

        switch(opcao) {
            case 1: {
                limparTerminal();
                Conta conta;
                conta.setCpf(cpf);

                if(cntrSConta->visualizar(&conta)) {
                    cout << "Dados da Conta:" << endl;
                    cout << "Nome: " << conta.getNome().getNome() << endl;
                    cout << "Cpf: " << conta.getCpf().getCpf() << endl;
                    cout << "Senha: " << conta.getSenha().getSenha() << endl << endl;
                    cout << voltar;
                    cin.ignore();
                    cin.get();
                } else {
                    cout << "Falha ao acessar a conta." << endl;
                    cout << voltar;
                }
                break;
            }

            case 2: {
                while(true) {
                    limparTerminal();
                    Conta conta;
                    conta.setCpf(cpf);
                    string nomeEntrada;
                    string senhaEntrada;
                    Nome nome;
                    Senha senha;

                    cout << "Digite novos dados: " << endl;
                    cout << "Novo Nome: ";
                    cin.ignore();
                    getline(cin, nomeEntrada);
                    cout << "Nova Senha: ";
                    cin >> senhaEntrada;

                    try {
                        nome.setNome(nomeEntrada);
                        senha.setSenha(senhaEntrada);
                    } catch(exception& invalid_argument) {
                        cout << RED << "Dados invalidos!" << RESET << endl;
                        cout << voltar;
                        cin.ignore();
                        cin.get();
                        continue;
                    }

                    conta.setNome(nome);
                    conta.setSenha(senha);
                    limparTerminal();

                    if(cntrSConta->editar(conta)) {
                        cout << GREEN << "Alterações feitas com sucesso" << RESET << endl;
                        cout << voltar;
                        cin.ignore();
                        cin.get();
                        break;
                    } else {
                        cout << "Falha ao editar Conta." << endl;
                        cout << voltar;
                        cin.ignore();
                        cin.get();
                        break;
                    }
                }
                break;
            }

            case 3: {
                if(cntrSConta->excluir(cpf)) {
                    cout << GREEN << "Exclusão feita com sucesso" << RESET << endl;
                    cout << voltar;
                    cin.ignore();
                    cin.get();
                    tela = false;
                    return true; // conta foi excluída
                } else {
                    cout << "Falha ao excluir Conta." << endl;
                    cout << voltar;
                    cin.ignore();
                    cin.get();
                    break;
                }
            }

            case 4: {
                tela = false;
                break;
            }

            default: {
                cout << RED << "Opção inválida!" << RESET << endl;
                cout << voltar;
                cin.ignore();
                cin.get();
                break;
            }
        }
    }
    return false;
}


void CntrIAInvestimentos::executar(Cpf cpf) {
    while(true) {
        limparTerminal();

        int opcao;

        cout << "Qual serviço deseja acessar?" << endl << endl;;
        cout << "1. Acessar Titulos." << endl;
        cout << "2. Acessar Pagamentos." << endl;
        cout << "3. Voltar" << endl;
        cout << "Sua opção: ";
        cin >> opcao;

        switch(opcao) {
            case 1: {
                executarTitulo(cpf);
                break;
            }
            case 2: {
                executarPagamento(cpf);
                break;
            }
            case 3: {
                return;
            }
        }
    }
}

void CntrIAInvestimentos::executarTitulo(Cpf cpf) {
    limparTerminal();

    int opcao;
    while(true) {
        cout << "Serviço de Titulos:" << endl << endl;
        cout << "1. Criar Titulo" << endl;
        cout << "2. Visualizar Titulos" << endl;
        cout << "3. Editar Titulo" << endl;
        cout << "4. Excluir Titulo" << endl;
        cout << "5. Voltar" << endl;
        cout << "Sua opção: ";

        cin >> opcao;

        switch(opcao) {
            case 1: {
                CntrIAInvestimentos::criarTitulo(&cpf);
                break;
            }
            case 2: {
                limparTerminal();

                vector<Titulo> titulosVisualizados = cntrSInvestimentos->visualizarTitulos(cpf);
                if (!titulosVisualizados.empty()) {
                    cout << "Dados dos Títulos:" << endl;
                    for (const auto& titulo : titulosVisualizados) {
                        cout << "-----------------------------" << endl;
                        cout << "Código: " << titulo.getCodigo().getCodigoTitulo() << endl;
                        cout << "Emissor: " << titulo.getEmissor().getNome() << endl;
                        cout << "Setor: " << titulo.getSetor().getSetor() << endl;
                        cout << "Emissão: " << titulo.getEmissao().getData() << endl;
                        cout << "Vencimento: " << titulo.getVencimento().getData() << endl;
                        cout << "Valor: R$" << titulo.getValor().getDinheiro() << endl;
                    }

                    cout << "Pressione Enter para continuar";
                    cin.ignore();
                    cin.get();
                    limparTerminal();
                } else {
                    cout << RED << "Nenhum título encontrado para o CPF informado." << RESET << endl;
                    cout << "Pressione Enter para continuar";
                    cin.ignore();
                    cin.get();
                }

                break;
            }

            case 3: {
                limparTerminal();

                string codigoTitulo;
                CodigoDeTitulo codigoDeTitulo;
                cout << "Digite o código do título que deseja editar: ";
                cin >> codigoTitulo;

                try {
                    codigoDeTitulo.setCodigoTitulo(codigoTitulo);
                }catch(const invalid_argument& e) {
                    limparTerminal();
                    cout << RED << "Erro: " << e.what() << RESET << endl;
                }

                ContainerTitulos* cntrTitulos = ContainerTitulos::getInstancia();

                vector<Titulo> titulosVisualizados = cntrTitulos->visualizarTitulos(cpf);
                bool encontrado = false;
                for (auto& titulo : titulosVisualizados) {
                    if (titulo.getCodigo().getCodigoTitulo() == codigoTitulo) {
                        // Coletar novos dados do título
                        string novoValor;
                        string novoVencimento;

                        Data vencimento;
                        Dinheiro dinheiro;

                        cout << "Digite o novo vencimento do título (DD-MM-AAAA): ";
                        cin >> novoVencimento;

                        cout << "Digite o novo valor do título: ";
                        cin >> novoValor;


                        try {
                            vencimento.setData(novoVencimento);
                            dinheiro.setDinheiro(novoValor);

                            // Atualizar os campos do título encontrado
                            titulo.setVencimento(vencimento);
                            titulo.setValor(dinheiro);
                        }catch(const invalid_argument& e) {
                            limparTerminal();
                            cout << RED << "Erro: " << e.what() << RESET << endl;
                        }

                        // Editar o título
                        if (cntrTitulos->editarTitulo(cpf, titulo)) {
                            cout << GREEN << "Título editado com sucesso." << RESET << endl;
                        } else {
                            cout << RED << "Falha ao editar o título." << RESET << endl;
                        }
                        encontrado = true;
                        break;
                    }
                }

                if (!encontrado) {
                    cout << RED << "Título com código " << codigoTitulo << " não encontrado." << RESET << endl;
                }

                cout << "Pressione Enter para continuar";
                cin.ignore();
                cin.get();
                limparTerminal();

                break;
            }

            case 4: {
                limparTerminal();
                string codigo;
                CodigoDeTitulo codigoDeTitulo;

                cout << "Digite o código do Titulo que deseja excluir: ";
                cin >> codigo;

                try {
                    limparTerminal();
                    cout << GREEN << "Titulo excluido com sucesso!" << RESET << endl;
                    codigoDeTitulo.setCodigoTitulo(codigo);
                    cntrSInvestimentos->excluirTitulo(cpf, codigoDeTitulo);
                }catch(const invalid_argument& e) {
                    limparTerminal();
                    cout << RED << "Erro: " << e.what() << RESET << endl;
                }

                break;
            }

            case 5: {
                return;
            }
        }
    }
}

void CntrIAInvestimentos::executarPagamento(Cpf cpf) {
    limparTerminal();

    int opcao;
    while(true) {
        cout << "Serviço de Pagamentos:" << endl << endl;
        cout << "1. Criar Pagamento" << endl;
        cout << "2. Visualizar Pagamentos" << endl;
        cout << "3. Editar Pagamentos" << endl;
        cout << "4. Excluir pagamento" << endl;
        cout << "5. Voltar" << endl;
        cout << "Sua opção: ";

        cin >> opcao;

        switch(opcao) {
            case 1: {
                CntrIAInvestimentos::criarPagamento(&cpf);
                break;
            }

            case 2: {
                limparTerminal();

                string codigoTitulo;
                CodigoDeTitulo codigoDeTitulo;
                cout << "Digite o código do título para visualizar os pagamentos: ";
                cin >> codigoTitulo;

                try {
                    codigoDeTitulo.setCodigoTitulo(codigoTitulo);
                } catch (const invalid_argument& e) {
                    limparTerminal();
                    cout << RED << "Erro: " << e.what() << RESET << endl;
                    break;
                }

                vector<Pagamento> pagamentosVisualizados = cntrSInvestimentos->visualizarPagamento(codigoDeTitulo);
                if (!pagamentosVisualizados.empty()) {
                    cout << endl << "Dados dos Pagamentos:" << endl;
                    for (const auto& pagamento : pagamentosVisualizados) {
                        cout << "-----------------------------" << endl;
                        cout << "Código: " << pagamento.getCodigo().getCodigoPagamento() << endl;
                        cout << "Data: " << pagamento.getData().getData() << endl;
                        cout << "Percentual: " << pagamento.getPercentual().getPercentual() << "%" << endl;
                        cout << "Estado: " << pagamento.getEstado().getEstado() << endl;
                    }

                    cout << "Pressione Enter para continuar";
                    cin.ignore();
                    cin.get();
                    limparTerminal();
                } else {
                    cout << RED << "Nenhum pagamento encontrado para o código de título informado." << RESET << endl;
                    cout << "Pressione Enter para continuar";
                    cin.ignore();
                    cin.get();
                    limparTerminal();
                }
                break;
            }

            case 3: {
                limparTerminal();

                string codigoPagamento, codigoTitulo;
                CodigoDePagamento codigoDePagamento;
                CodigoDeTitulo codigoDeTitulo;

                cout << "Digite o código do Titulo do pagamento que deseja editar: ";
                cin >> codigoTitulo;

                cout << "Digite o código do pagamento que deseja editar: ";
                cin >> codigoPagamento;

                try {
                    codigoDeTitulo.setCodigoTitulo(codigoTitulo);
                    codigoDePagamento.setCodigoPagamento(codigoPagamento);
                }catch(const invalid_argument& e) {
                    limparTerminal();
                    cout << RED << "Erro: " << e.what() << RESET << endl;
                }

                ContainerPagamentos* cntrPagamentos = ContainerPagamentos::getInstancia();

                vector<Pagamento> pagamentosVisualizados = cntrPagamentos->visualizarPagamentos(codigoDeTitulo);
                bool encontrado = false;
                for (auto& pagamento : pagamentosVisualizados) {
                    if (pagamento.getCodigo().getCodigoPagamento() == codigoDePagamento.getCodigoPagamento()) {
                        // Coletar novos dados do Pagamento
                        string novaData,novoEstado;
                        int novoPercentual;

                        Data data;
                        Percentual percentual;
                        Estado estado;

                        cout << "Editar pagamento com o código: " << codigoDePagamento.getCodigoPagamento() << endl << endl;

                        cout << "Digite a nova data do pagamento (DD-MM-AAAA): ";
                        cin >> novaData;

                        cout << "Digite o novo percentual do Pagamento: ";
                        cin >> novoPercentual;

                        cout << "Digite o novo estado do Pagamento: ";
                        cin >> novoEstado;


                        try {
                            data.setData(novaData);
                            percentual.setPercentual(novoPercentual);
                            estado.setEstado(novoEstado);
                        }catch(const invalid_argument& e) {
                            limparTerminal();
                            cout << RED << "Erro: " << e.what() << RESET << endl;
                        }

                        // Atualizar os campos do pagamento encontrado
                        pagamento.setData(data);
                        pagamento.setPercentual(percentual);
                        pagamento.setEstado(estado);

                        if (cntrPagamentos->editarPagamento(codigoDeTitulo, pagamento)) {
                            cout << GREEN << "Pagamento editado com sucesso." << RESET << endl;
                        } else {
                            cout << RED << "Falha ao editar o pagamento." << RESET << endl;
                        }
                        encontrado = true;
                        break;
                    }
                }

                if (!encontrado) {
                    cout << "Pagamento com código: " << codigoDePagamento.getCodigoPagamento() << " não encontrado." << endl;
                }

                cout << "Pressione Enter para continuar";
                cin.ignore();
                cin.get();

                limparTerminal();
                break;
            }

            case 4: {
                limparTerminal();

                CodigoDePagamento codigoDePagamento;
                string codigo;

                cout << "Digite o código de pagamento que deseja exlcluir: ";
                cin >> codigo;

                try {
                    codigoDePagamento.setCodigoPagamento(codigo);
                }catch(const invalid_argument& e) {
                    limparTerminal();
                    cout << RED << "Erro: " << e.what() << RESET << endl;
                }

                if (cntrSInvestimentos->excluirPagamento(codigoDePagamento)) {
                    cout << GREEN << "Pagamento excluido com sucesso!" << RESET << endl;

                } else {
                    cout << RED << "Falha ao excluir pagamento para o código: " << codigo << RESET << endl;
                }

                break;
            }

            case 5: {
                return;
                break;
            }

            default: {
                limparTerminal();
                cout << RED << "Opção inválida!" << RESET << endl;
                cout << "Pressione Enter para continuar";
                cin.ignore();
                cin.get();
                break;
            }
        }
    }

}

bool CntrIAInvestimentos::criarTitulo(Cpf *cpf) {
    limparTerminal();

    //Pega a data real do usuario
    time_t tempo_atual = time(nullptr);
    tm *data_hora = localtime(&tempo_atual);

    int dia = data_hora->tm_mday;
    int mes = data_hora->tm_mon + 1; // tm_mon vai de 0 a 11, então soma 1
    int ano = data_hora->tm_year + 1900; // tm_year é o ano desde 1900, então soma 1900

    // Cria uma string para armazenar a data no formato DD-MM-AAAA
    stringstream ss;
    ss << setfill('0') << setw(2) << dia << "-" << setfill('0') << setw(2) << mes << "-" << setw(4) << ano;
    string dataAux = ss.str();

    // Gera um código aleatório
    int codigoAleatorio = distrib(gen);

    //Classes Dominios para o Titulo
    CodigoDeTitulo codigoDetitulos;
    Setor setor;
    Data emissao,vencimento;
    Dinheiro valor;

    Conta conta;
    try {
        conta = buscarConta(*cpf);
    } catch(const invalid_argument &exp) {
        cout << RED << exp.what() << RESET << endl;
        return false;
    }

    Titulo titulo;

    int opcao;
    string entrada,vencimentoStr,dinheiroStr;

    while(true) {
        cout << "Escolha qual titulos de renda fixa deseja:" << endl;
        cout << "1. Certificado de Depósito Bancário (CDB)." << endl;
        cout << "2. Certificado de Recebíveis do Agronégócio (CRA)." << endl;
        cout << "3. Certificado de Recebíveis Imobiliários (CRI)." << endl;
        cout << "4. Letra de Crédito do Agronegócio (LCA)." << endl;
        cout << "5. Letra de Crédito Imobiliário (LCI)." << endl;
        cout << "6. Voltar" << endl;
        cout << "Sua opção: ";

        cin >> opcao;

        try{
            codigoDetitulos.setCodigoTitulo(codigoDetitulos.TITULOS_VALIDOS[opcao - 1] + to_string(codigoAleatorio));
        }catch(const invalid_argument &exp) {
            cout << RED << exp.what() << RESET << endl;
            break;
            return false;
    }

        switch(opcao) {
            case 1:
            case 2:
            case 3:
            case 4:
            case 5:
                 {
                limparTerminal();
                cout << "Dos setores acima qual você se identifica?" << endl;

                int i = 1;

                for(const string& s : setor.SETOR_VALIDOS){
                    cout << i << ". " << s << endl;
                    i++;
                }

                cout << "Sua opção: ";
                cin >> opcao;

                limparTerminal();
                cout << "Para quando você quer o vencimento(DD-MM-AAAA): ";
                cin >> vencimentoStr;

                // Verifica se a data de vencimento é anterior a data atual
                tm data_vencimento = {};
                stringstream ss_venc(vencimentoStr);
                ss_venc >> get_time(&data_vencimento, "%d-%m-%Y");

                if (mktime(&data_vencimento) < mktime(data_hora)) {
                    cout << RED << "A data de vencimento não pode ser anterior à data atual." << RESET << endl;
                    return false;
                }

                cout << "Qual valor será investido: ";
                cin >> dinheiroStr;

                try {
                    setor.setSetor(setor.SETOR_VALIDOS[opcao - 1]);
                    vencimento.setData(vencimentoStr);
                    emissao.setData(dataAux);
                    valor.setDinheiro(dinheiroStr);

                    titulo.setCodigo(codigoDetitulos);
                    titulo.setEmissor(conta.getNome());
                    titulo.setSetor(setor);
                    titulo.setEmissao(emissao);
                    titulo.setVencimento(vencimento);
                    titulo.setValor(valor);

                }catch(const invalid_argument &exp) {
                    cout << RED << exp.what() << RESET << endl;
                    return false;
                }

                limparTerminal();

                if (cntrSInvestimentos->criarTitulo(*cpf, titulo)) {
                    cout << GREEN << "Título criado com sucesso!" << RESET << endl;
                } else {
                    cout << RED << "Falha ao criar o título. " << codigoDetitulos.getCodigoTitulo() << RESET << endl;
                }

                return false;

            }
            case 6: {return false;}
        }
    }

    return false;
}

bool CntrIAInvestimentos::criarPagamento(Cpf *cpf) {
    limparTerminal();

    // Pega a data real do usuário
    time_t tempo_atual = time(nullptr);
    tm *data_hora = localtime(&tempo_atual);

    int dia = data_hora->tm_mday;
    int mes = data_hora->tm_mon + 1; // tm_mon vai de 0 a 11, então soma 1
    int ano = data_hora->tm_year + 1900; // tm_year é o ano desde 1900, então soma 1900

    // Cria uma string para armazenar a data no formato DD-MM-AAAA
    stringstream ss;
    ss << setfill('0') << setw(2) << dia << "-" << setfill('0') << setw(2) << mes << "-" << setw(4) << ano;
    string dataAux = ss.str();

    // Gera um código aleatório
    int codigoAleatorio = distrib(gen);

    CodigoDeTitulo codigoDeTitulo;

    // Classes Dominios para o Pagamento
    CodigoDePagamento codigoDePagamento;
    Data data;
    Percentual percentual;
    Estado estado;
    Pagamento pagamento;

    int percent;
    string codTituloStr,estadoStr;

    cout << "Digite o código de titulo que deseja fazer um pagamento: ";
    cin >> codTituloStr;
    cout << "Sua opção: ";

    limparTerminal();
    cout << "Pagamento para um Título" << endl;
    cout << "Digite o percentual do pagamento: ";
    cin >> percent;

    cout << "Digite o estado do pagamento: ";
    cin >> estadoStr;

    try{
        codigoDeTitulo.setCodigoTitulo(codTituloStr);
        codigoDePagamento.setCodigoPagamento(to_string(codigoAleatorio));
        data.setData(dataAux);
        percentual.setPercentual(percent);
        estado.setEstado(estadoStr);

        pagamento.setCodigo(codigoDePagamento);
        pagamento.setData(data);
        pagamento.setPercentual(percentual);
        pagamento.setEstado(estado);
    }catch(const invalid_argument &exp) {
        cout << RED << exp.what() << RESET << endl;
        return false;
    }

    limparTerminal();

    if (cntrSInvestimentos->criarPagamento(codigoDeTitulo, pagamento)) {
        cout << GREEN << "Pagamento criado com sucesso!" << RESET << endl;
        return true;
    } else {
        cout << RED << "Falha ao criar pagamento para o código: " << codigoDePagamento.getCodigoPagamento() << RESET << endl;
        return false;
    }

    return false;
}

Conta CntrIAInvestimentos::buscarConta(Cpf cpf) {
    if (cntrSConta == nullptr) {
        throw runtime_error("Ponteiro cntrSConta não inicializado.");
    }

    Conta conta;
    conta.setCpf(cpf);
    if (cntrSConta->visualizar(&conta)) {
        return conta;
    } else {
        throw invalid_argument("Conta não encontrada.");
    }
}

//-------------------------------------------------------------------//
bool CntrISC::criar(Conta conta) {
    ContainerConta *conConta;
    conConta = ContainerConta::getInstancia();

    return conConta->criar(conta);

}

bool CntrISC::visualizar(Conta* conta) {
    ContainerConta *conConta;

    conConta = ContainerConta::getInstancia();
    return conConta->existe(conta);
}

bool CntrISC::editar(Conta conta) {
    ContainerConta *conConta;
    conConta = ContainerConta::getInstancia();

    return conConta->editar(conta);
}

bool CntrISC::excluir(Cpf cpf) {
    ContainerConta *conConta;
    conConta = ContainerConta::getInstancia();

    return conConta->excluir(cpf);
}

bool CntrISI::criarTitulo(Cpf cpf, Titulo titulo) {
    ContainerTitulos *conTitulo;

    conTitulo = ContainerTitulos::getInstancia();

    return conTitulo->criarTitulo(cpf,titulo);
}

bool CntrISI::criarPagamento(CodigoDeTitulo codigoDeTitulo, Pagamento pagamento) {
    ContainerPagamentos *conPagamento;
    ContainerTitulos *conTitulos;

    conPagamento = ContainerPagamentos::getInstancia();
    conTitulos = ContainerTitulos::getInstancia();

    if(conTitulos->existe(codigoDeTitulo))
        return conPagamento->criarPagamento(codigoDeTitulo,pagamento);

    return false;
}

vector<Titulo> CntrISI::visualizarTitulos(Cpf cpf) {
    ContainerTitulos *conTitulo = ContainerTitulos::getInstancia();
    return conTitulo->visualizarTitulos(cpf);
}

vector<Pagamento> CntrISI::visualizarPagamento(CodigoDeTitulo codigoDeTitulo) {
    ContainerPagamentos *conPagamento = ContainerPagamentos::getInstancia();
    return conPagamento->visualizarPagamentos(codigoDeTitulo);
}

bool CntrISI::editarTitulo(Cpf cpf, Titulo titulo) {
    ContainerTitulos *conTitulo;
    conTitulo = ContainerTitulos::getInstancia();

    return conTitulo->editarTitulo(cpf, titulo);
}

bool CntrISI::editarPagamento(CodigoDeTitulo codigoDeTitulo, Pagamento pagamento) {
    ContainerPagamentos *conPagamento;
    conPagamento = ContainerPagamentos::getInstancia();

    return conPagamento->editarPagamento(codigoDeTitulo, pagamento);
}

bool CntrISI::excluirTitulo(Cpf cpf, CodigoDeTitulo codigodetitulo) {
    ContainerTitulos* conTitulos = ContainerTitulos::getInstancia();

    bool resultado = conTitulos->excluirTitulo(cpf, codigodetitulo);

    // Se o título foi excluído com sucesso, exclui também todos os pagamentos associados
    if (resultado) {
        ContainerPagamentos* conPagamentos = ContainerPagamentos::getInstancia();
        // Exclui todos os pagamentos associados ao título
        conPagamentos->excluirPagamentosPorTitulo(codigodetitulo);
    }

    return resultado;
}

bool CntrISI::excluirPagamento(CodigoDePagamento codigodepagamento) {
    ContainerPagamentos *conPagamento;
    conPagamento = ContainerPagamentos::getInstancia();

    return conPagamento->excluirPagamento(codigodepagamento);
}

bool CntrISAutenticacao::autenticar(Cpf cpf, Senha senha) {
    ContainerConta *conConta;
    conConta = ContainerConta::getInstancia();
    Conta contaProvisoria;
    Conta contaReal;
    contaProvisoria.setCpf(cpf);
    contaProvisoria.setSenha(senha);
    if (conConta->existe(&contaProvisoria)) {
        contaReal = conConta->visualizar(&contaProvisoria);
        if(contaReal.getSenha().getSenha() == senha.getSenha()){
            return true;
        }
    }

    return false;
}
