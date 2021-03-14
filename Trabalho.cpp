// Trabalho.cpp : Este arquivo contém a função 'main'. A execução do programa começa e termina ali.
//

#include <iostream>
#include <fstream>  
using namespace std;

void criaArquivo();

struct Time
{
	string nome;
	int pontos;
	int vitorias;
	int derrotas;
	int empates;
};

int main()
{
	criaArquivo();
	int escolhaDoQueFazer;
	cout << "Bem vindo à lista de times do Brasileirão 2021! O quê você deseja fazer? Insira o número correspondente à sua escolha." << endl;
	cout << "1. Inserir um time" << endl;
	cout << "2. Ver a tabela do Brasileirão" << endl;
	cout << "3. Editar as informações de algum time" << endl;
	cout << "4. Deletar algum time" << endl;
	cin >> escolhaDoQueFazer;
	switch (escolhaDoQueFazer) {
		case(1):
			cout << "Funcionalidade indisponível no momento";
			break;
		case(2):
			cout << "Funcionalidade indisponível no momento";
			break;
		case(3):
			cout << "Funcionalidade indisponível no momento";
			break;
		case(4):
			cout << "Funcionalidade indisponível no momento";
			break;
		default:
			cout << "Escolha inválida";
			break;
	}

}

void criaArquivo() {
	struct stat buffer;
	string nomeArquivo = "listaTimes.txt";
	bool verificaSeArquivoExiste = stat(nomeArquivo.c_str(), &buffer) == 0;

	if (!verificaSeArquivoExiste) {
		ofstream outfile(nomeArquivo);

		outfile << "listona cabulosa" << endl;
		outfile.close();
	}
}

