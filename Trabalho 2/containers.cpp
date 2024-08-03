#include <iostream>
#include <algorithm>
#include "containers.h"

ContainerConta* ContainerConta::instancia = nullptr;

ContainerConta* ContainerConta::getInstancia() {
    if (instancia == 0)
        instancia = new ContainerConta();
    return instancia;
}

bool ContainerConta::criar(Conta conta){
    return container.insert(make_pair(conta.getCpf().getCpf(), conta)).second;
}

bool ContainerConta::excluir(Cpf cpf) {
    // Primeiro, verificar se a conta existe
    auto itConta = container.find(cpf.getCpf());
    if (itConta == container.end()) {
        return false; // Conta não encontrada
    }

    // Obter os títulos associados à conta
    vector<Titulo> titulos = ContainerTitulos::getInstancia()->visualizarTitulos(cpf);

    // Excluir todos os títulos associados à conta
    for (const auto& titulo : titulos) {
        CodigoDeTitulo codigoTitulo = titulo.getCodigo();
        ContainerTitulos::getInstancia()->excluirTitulo(cpf, codigoTitulo);

        // Excluir todos os pagamentos associados ao título
        ContainerPagamentos::getInstancia()->excluirPagamentosPorTitulo(codigoTitulo);
    }

    // Excluir a conta
    container.erase(itConta);
    return true; // Conta excluída com sucesso
}

Conta ContainerConta::visualizar(Conta* conta){
    map<string, Conta>::iterator it = container.find(conta->getCpf().getCpf());
    if(it != container.end()){
        *conta = it->second;
        return it->second;
    }
    else{
        throw runtime_error("");
    }
}

bool ContainerConta::existe(Conta* conta){
    map<string, Conta>::iterator it = container.find(conta->getCpf().getCpf());
    if(it != container.end()){
        *conta = it->second;
        return true;
    }
    return false;
}

bool ContainerConta::editar(Conta conta){
    map<string, Conta>::iterator it = container.find(conta.getCpf().getCpf());
    if(it != container.end()){
        it->second = conta;
        return true;
    }
    return false;
}

ContainerTitulos* ContainerTitulos::instancia = nullptr;

ContainerTitulos* ContainerTitulos::getInstancia() {
    if (instancia == nullptr) {
        instancia = new ContainerTitulos();
    }
    return instancia;
}

bool ContainerTitulos::criarTitulo(Cpf& cpf, Titulo& titulo) {
    auto& titulos = container[cpf.getCpf()];

    if(titulos.size() < 5) {
        for (const auto& t : titulos) {
            if (t.getCodigo().getCodigoTitulo() == titulo.getCodigo().getCodigoTitulo()) {
                return false; // O título já existe
            }
        }
        titulos.push_back(titulo);
        return true; // Adicionado com sucesso
    }

    return false;
}

bool ContainerTitulos::excluirTitulo(Cpf& cpf, CodigoDeTitulo& codigoTitulo) {
    auto it = container.find(cpf.getCpf());
    if (it != container.end()) {
        auto& titulos = it->second;
        auto tituloIt = remove_if(titulos.begin(), titulos.end(),
            [&codigoTitulo](const Titulo& titulo) {
                return titulo.getCodigo().getCodigoTitulo() == codigoTitulo.getCodigoTitulo();
            });
        if (tituloIt != titulos.end()) {
            titulos.erase(tituloIt, titulos.end());

            // Excluir todos os pagamentos associados ao título
            ContainerPagamentos::getInstancia()->excluirPagamentosPorTitulo(codigoTitulo);

            return true; // Título excluído com sucesso
        }
    }
    return false; // Título não encontrado
}

vector<Titulo> ContainerTitulos::visualizarTitulos(Cpf& cpf) {
    auto it = container.find(cpf.getCpf());
    if (it != container.end()) {
        return it->second;
    }
    return vector<Titulo>(); // Retorna um vetor vazio se nenhum título for encontrado
}

bool ContainerTitulos::existe(CodigoDeTitulo& codigoDeTitulo) {
    for (const auto& pair : container) {
        for (const auto& titulo : pair.second) {
            if (titulo.getCodigo().getCodigoTitulo() == codigoDeTitulo.getCodigoTitulo()) {
                return true; // Título encontrado
            }
        }
    }
    return false; // Título não encontrado
}

bool ContainerTitulos::editarTitulo(Cpf& cpf, Titulo& tituloAtualizado) {
    auto it = container.find(cpf.getCpf());
    if(it != container.end()) {
        for (auto& titulo : it->second) {
            if (titulo.getCodigo().getCodigoTitulo() == tituloAtualizado.getCodigo().getCodigoTitulo()) {
                titulo.setVencimento(tituloAtualizado.getVencimento());
                titulo.setValor(tituloAtualizado.getValor());
                return true;
            }
        }
    }
    return false;
}

ContainerPagamentos* ContainerPagamentos::instancia = nullptr;

ContainerPagamentos* ContainerPagamentos::getInstancia() {
    if (instancia == nullptr) {
        instancia = new ContainerPagamentos();
    }
    return instancia;
}

bool ContainerPagamentos::criarPagamento(CodigoDeTitulo& codigoDeTitulo, Pagamento& pagamento) {
    auto& pagamentos = container[codigoDeTitulo.getCodigoTitulo()];
    if(pagamentos.size() < 10) {
        for (const auto& p : pagamentos) {
            if (p.getCodigo().getCodigoPagamento() == pagamento.getCodigo().getCodigoPagamento()) {
                return false; // O pagamento já existe
            }
        }
        pagamentos.push_back(pagamento);
        return true; // Adicionado com sucesso
    }

    return false;
}

bool ContainerPagamentos::excluirPagamento(CodigoDePagamento& codigoDePagamento) {
    for (auto it = container.begin(); it != container.end(); ++it) {
        auto& pagamentos = it->second;
        auto pagamentoIt = remove_if(pagamentos.begin(), pagamentos.end(),
            [&codigoDePagamento](const Pagamento& pagamento) {
                return pagamento.getCodigo().getCodigoPagamento() == codigoDePagamento.getCodigoPagamento();
            });
        if (pagamentoIt != pagamentos.end()) {
            pagamentos.erase(pagamentoIt, pagamentos.end());
            return true; // Pagamento encontrado e removido
        }
    }
    return false; // Pagamento não encontrado
}

bool ContainerPagamentos::excluirPagamentosPorTitulo(CodigoDeTitulo& codigoDeTitulo) {
    auto it = container.find(codigoDeTitulo.getCodigoTitulo());
    if (it != container.end()) {
        container.erase(it); // Remove todos os pagamentos associados ao título
        return true; // Pagamentos excluídos com sucesso
    }
    return false; // Título não encontrado
}


vector<Pagamento> ContainerPagamentos::visualizarPagamentos(CodigoDeTitulo& codigoDeTitulo) {
    auto it = container.find(codigoDeTitulo.getCodigoTitulo());
    if (it != container.end()) {
        return it->second;
    }
    return vector<Pagamento>(); // Retorna um vetor vazio se nenhum título for encontrado
}

bool ContainerPagamentos::editarPagamento(CodigoDeTitulo& codigoDeTitulo, Pagamento& pagamentoAtualizado) {
    auto it = container.find(codigoDeTitulo.getCodigoTitulo());
    if(it != container.end()) {
        for (auto& pagamento : it->second) {
            if (pagamento.getCodigo().getCodigoPagamento() == pagamentoAtualizado.getCodigo().getCodigoPagamento()) {
                pagamento.setData(pagamentoAtualizado.getData());
                pagamento.setPercentual(pagamentoAtualizado.getPercentual());
                pagamento.setEstado(pagamentoAtualizado.getEstado());
                return true;
            }
        }
    }
    return false;
}
