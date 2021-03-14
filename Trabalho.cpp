// Trabalho.cpp : Este arquivo contém a função 'main'. A execução do programa começa e termina ali.
//

#include <iostream>
#include <fstream>  
using namespace std;

struct Time
{
	string nome;
	int pontos;
	int vitorias;
	int derrotas;
	int empates;
};

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
int main()
{
	criaArquivo();
}

