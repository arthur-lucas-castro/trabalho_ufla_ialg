// Trabalho.cpp : Este arquivo contém a função 'main'. A execução do programa começa e termina ali.
//

#include <iostream>
#include <fstream>  
#include <sstream>
#include <vector>
#include <iomanip>
using namespace std;

struct Time
{
	char nome[10];
	int pontos;
	int vitorias;
	int derrotas;
	int empates;
	int posicao;
};

void EditarCampo(int escolhaUsuario, int posicaoTime, Time time);
void insereTime();
void leTime();
void editarTime();

string nomeArquivo = "listaTimes.txt";



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
			repetir = false;
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

	arq.close();
}

void leTime() {
	ifstream arq;

	arq.open(nomeArquivo);	

	Time time;
	cout << '|' << setw(10) << "NOME" << '|' << setw(10) << "PONTOS" << '|' << setw(10) << "VITORIAS" << '|' << setw(10) << "EMPATES" << '|' << setw(10) << "DERROTAS" << '|' << endl;
	cout << '|' << "----------" << '|' << setw(10) << "----------" << '|' << setw(10) << "----------" << '|' << setw(10) << "----------" << '|' << setw(10) << "----------" << "|" << endl;
	while (arq.read((char*)&time, sizeof(Time)))
	{
		cout << '|' << setw(10) << time.nome << '|' << setw(10) << time.pontos << '|' << setw(10) << time.vitorias << '|' << setw(10) << time.empates << '|' << setw(10) << time.derrotas << '|' << endl;
		cout << '|' << "----------" << '|' << setw(10) << "----------" << '|' << setw(10) << "----------" << '|' << setw(10) << "----------" << '|' << setw(10) << "----------" << "|" << endl;
		//cout << time.nome << " " << time.pontos << " " << endl;
	}


	arq.close();
}

void editarTime() {

	ifstream arq(nomeArquivo);

	ofstream arqEscrita(nomeArquivo, fstream::out | fstream::in);
	string nome;
	int escolhaDoQueFazer;
	cout << "Qual o criterio para a ediçao:" << endl;
	cout << "1. Por nome do time" << endl;
	cout << "2. Por colocaçao do time na tabela" << endl;
	cin >> escolhaDoQueFazer;
	Time time;
	int posicaoInicioTime = 0;
	switch (escolhaDoQueFazer)
	{
		case 1:
			cout << "Digite o nome do Time que deseja editar:" << endl;
			cin >> nome;
			while (arq.read((char*)&time, sizeof(Time)))
			{
				if (time.nome == nome) {
				
					cout << "Encontramos o time desejado, Atualmente essa é a situaçao dele:" << endl;
					cout << "Nome: " << time.nome << endl;
					cout << "Pontos: " << time.pontos << endl;
					cout << "Vitorias: " << time.vitorias << endl;
					cout << "Empates: " << time.empates << endl;
					cout << "Derrotas: " << time.derrotas << endl;
					cout << "Agora escolha o que voce vai editar: " << endl;
					cout << "1. Nome." << endl;
					cout << "2. Vitorias." << endl;
					cout << "3.	Empates" << endl;
					cout << "4. Derrotas" << endl;
					cout << "-1. Voltar" << endl;
					cin >> escolhaDoQueFazer;
					EditarCampo(escolhaDoQueFazer, posicaoInicioTime, time);
				}
				posicaoInicioTime = arq.tellg();//arq.tellg() pega a posiçao da ultima leitura
			}
			break;
		case 2:
			break;
		default:
			break;
	}
	arq.close();
}


void EditarCampo(int escolhaUsuario, int posicaoTime, Time time) {
	ofstream arqEscrita(nomeArquivo, fstream::out | fstream::in);
	switch (escolhaUsuario)
	{
	case 1:
		arqEscrita.seekp(posicaoTime);//aponta o ponteiro de escrita para a posicao desejada
		cout << "Digite o novo nome do time:" << endl;
		cin >> time.nome;
		arqEscrita.write((char*)&time, sizeof(Time));
		break;
	case 2:
		arqEscrita.seekp(posicaoTime);//aponta o ponteiro de escrita para a posicao desejada
		cout << "Digite o novo numero de vitorias do time:" << endl;
		cin >> time.vitorias;
		time.pontos = (time.vitorias * 3) + time.empates;
		arqEscrita.write((char*)&time, sizeof(Time));
		break;
	case 3:
		arqEscrita.seekp(posicaoTime);//aponta o ponteiro de escrita para a posicao desejada
		cout << "Digite o novo numero de empates do time:" << endl;
		cin >> time.empates;
		time.pontos = (time.vitorias * 3) + time.empates;
		arqEscrita.write((char*)&time, sizeof(Time));
		break;
	case 4:
		arqEscrita.seekp(posicaoTime);//aponta o ponteiro de escrita para a posicao desejada
		cout << "Digite o novo numero de derrotas do time:" << endl;
		cin >> time.derrotas;
		arqEscrita.write((char*)&time, sizeof(Time));
		break;
	case -1:
		break;
	default:

		break;
	}
}

