// Trabalho.cpp : Este arquivo contém a função 'main'. A execução do programa começa e termina ali.
//

#include <iostream>
#include <fstream>  
#include <sstream>
#include <vector>
using namespace std;

void insereTime();
void leTime();
void editarTime();
string nomeArquivo = "listaTimes.txt";

struct Time
{
	char nome[10];
	int pontos;
	int vitorias;
	int derrotas;
	int empates;
};

int main()
{
	int escolhaDoQueFazer;
	bool repetir = true;
	while (repetir) {
		cout << "Bem vindo à lista de times do Brasileirão 2021! O quê você deseja fazer? Insira o número correspondente à sua escolha." << endl;
		cout << "1. Inserir um time" << endl;
		cout << "2. Ver a tabela do Brasileirão" << endl;
		cout << "3. Editar as informações de algum time" << endl;
		cout << "4. Deletar algum time" << endl;
		cout << "5. Finalizar programa" << endl;
		cin >> escolhaDoQueFazer;
		switch (escolhaDoQueFazer) {
		case(1):
			insereTime();
			break;
		case(2):
			leTime();
			break;
		case(3):
			editarTime();
			break;
		case(4):
			cout << "Funcionalidade indisponível no momento";
			break;
		case(5):
			repetir = false;
			break;
		default:
			cout << "Escolha inválida";
			break;
		}
	}	
}

void insereTime() {
	ofstream arq(nomeArquivo, fstream::app);

	Time time;
	cin >> time.nome >> time.pontos >> time.vitorias >> time.derrotas >> time.empates;
	arq.write((char*)&time, sizeof(time));

	//arq << time.nome << ";" << time.pontos << ";" << time.vitorias << ";" << time.derrotas << ";" << time.empates << ";" << endl;
	arq.close();
}

void leTime() {
	ifstream arq;

	arq.open(nomeArquivo);	

	Time time;

	while (arq.read((char*)&time, sizeof(Time)))
	{
		cout << time.nome << " " << time.pontos << " " << endl;
	}


	arq.close();
}

void editarTime() {

	ifstream arq(nomeArquivo);

	ofstream arqEscrita(nomeArquivo, fstream::out | fstream::in);
	string nome;
	cin >> nome;
	Time time;
	int posicaoItemAnterior = 0;
	while (arq.read((char*)&time, sizeof(Time)))
	{		
		if (time.nome == nome) {
			
			arqEscrita.seekp(posicaoItemAnterior);//aponta o ponteiro de escrita para a posicao desejada
			cin >> time.nome;
			arqEscrita.write((char*)&time, sizeof(Time));
		}
		posicaoItemAnterior = arq.tellg();//arq.tellg() pega a posiçao da ultima leitura
	}
	arq.close();
}

