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

void EditarCampo(int escolhaUsuario, int posicaoTime, Time time, vector<int> posicoesTodosItens);
void insereTime();
void leTime();
void editarTime();
void quickSort(vector<int> posicoesTodosItens, int inicio, int final);
int particionar(vector<int> posicoesTodosItens, int inicio, int final);
void trocar(int pos1, int pos2);
void deletarTime();
vector<int> getAllposicoes();

string nomeArquivo = "listaTimes.dat";



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
			deletarTime();
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
	ofstream arq(nomeArquivo, fstream::app | fstream::binary );

	Time time;
	cin >> time.nome >> time.pontos >> time.vitorias >> time.derrotas >> time.empates;
	cout << sizeof(Time) << endl;
	cout << sizeof(time) << endl;
	arq.write((char*)&time, sizeof(Time));
	arq.close();
}

void leTime() {
	ifstream arq(nomeArquivo,  fstream::binary);

	
	Time time;
	cout << '|' << setw(10) << "NOME" << '|' << setw(10) << "PONTOS" << '|' << setw(10) << "VITORIAS" << '|' << setw(10) << "EMPATES" << '|' << setw(10) << "DERROTAS" << '|' << endl;
	cout << '|' << "----------" << '|' << setw(10) << "----------" << '|' << setw(10) << "----------" << '|' << setw(10) << "----------" << '|' << setw(10) << "----------" << "|" << endl;
	while (arq.read((char*)&time, sizeof(Time)))
	{
		if (strlen(time.nome) > 0) {
			cout << '|' << setw(10) << time.nome << '|' << setw(10) << time.pontos << '|' << setw(10) << time.vitorias << '|' << setw(10) << time.empates << '|' << setw(10) << time.derrotas << '|' << endl;
			cout << '|' << "----------" << '|' << setw(10) << "----------" << '|' << setw(10) << "----------" << '|' << setw(10) << "----------" << '|' << setw(10) << "----------" << "|" << endl;
		}
		//cout << time.nome << " " << time.pontos << " " << endl;
	}
	

	arq.close();
}

vector<int> getAllposicoes() {
	ifstream arq(nomeArquivo, fstream::binary);
	Time time;
	vector<int> posicoes;
	int posicaoInicioTime = 0;
	while (arq.read((char*)&time, sizeof(Time)))
	{

		if (strlen(time.nome) > 0) {
			posicoes.push_back(posicaoInicioTime);

		}
		posicaoInicioTime = arq.tellg();//arq.tellg() pega a posiçao da ultima leitura
	}
	return posicoes;
}
void editarTime() {

	ifstream arq(nomeArquivo, fstream::binary);

	string nome;
	int escolhaDoQueFazer;
	cout << "Qual o criterio para a ediçao:" << endl;
	cout << "1. Por nome do time" << endl;
	cout << "2. Por colocaçao do time na tabela" << endl;
	cin >> escolhaDoQueFazer;
	int posicaoInicioTime = 0;
	switch (escolhaDoQueFazer)
	{
	case 1:
		arq.seekg(0);
		cout << "Digite o nome do Time que deseja editar:" << endl;
		cin >> nome;

		Time time;
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
				EditarCampo(escolhaDoQueFazer, posicaoInicioTime, time, getAllposicoes());
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


void EditarCampo(int escolhaUsuario, int posicaoTime, Time time, vector<int> posicoesTodosItens) {
	//ofstream arqEscrita(nomeArquivo, fstream::out | fstream::in );
	ofstream arqEscrita(nomeArquivo, fstream::out | fstream::in | fstream::binary);
	ifstream arq(nomeArquivo, ios::binary);
	int size = sizeof(Time);
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
		arqEscrita.close();
		
		quickSort(posicoesTodosItens, arqEscrita.beg, posicoesTodosItens.size()-1);
		break;
	case 3:
		arqEscrita.seekp(posicaoTime);//aponta o ponteiro de escrita para a posicao desejada
		cout << "Digite o novo numero de empates do time:" << endl;
		cin >> time.empates;
		time.pontos = (time.vitorias * 3) + time.empates;
		arqEscrita.write((char*)&time, sizeof(Time));
		arqEscrita.close();
		quickSort(posicoesTodosItens, arqEscrita.beg, posicoesTodosItens.size() - 1);
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
	arqEscrita.close();
}
void quickSort(vector<int> posicoesTodosItens, int inicio, int final) {


	int size = sizeof(Time);
	ofstream arqEscrita(nomeArquivo, fstream::out | fstream::in | fstream::binary);
	if (inicio < final)
	{
		int pi = particionar(posicoesTodosItens, inicio, final);
		quickSort(posicoesTodosItens, inicio, pi - 1);
		quickSort(posicoesTodosItens, pi + 1, final);
	}
	arqEscrita.close();
}
int particionar(vector<int> posicoesTodosItens, int inicio, int final)
{
	Time time;
	ifstream arq(nomeArquivo, fstream::binary);
	int size = sizeof(Time);
	arq.seekg(posicoesTodosItens[final], arq.beg);

	arq.read((char*)&time, sizeof(Time));
	Time timePivo = time;
    int i = (inicio - 1);

    for (int j = inicio; j <= final-1; j++)
    {
		arq.seekg(posicoesTodosItens[j], arq.beg);

		arq.read((char*)&time, sizeof(Time));
        if (time.pontos >= timePivo.pontos)
        {
			if (time.pontos == timePivo.pontos) {
				if (time.vitorias > timePivo.vitorias) {
					i++;
					trocar(posicoesTodosItens[i], posicoesTodosItens[j]);
				}
			}
			else {
				i++;
				trocar(posicoesTodosItens[i], posicoesTodosItens[j]);
			}

        }
    }
    trocar(posicoesTodosItens[i+1], posicoesTodosItens[final]);
	arq.close();
    return (i + 1);
}
void trocar(int pos1, int pos2)
{
	ofstream arqEscrita(nomeArquivo, fstream::out | fstream::in | fstream::binary);
	ifstream arq(nomeArquivo);
	arq.seekg(pos1, arq.beg);
	Time time;
	arq.read((char*)&time, sizeof(Time));
    Time aux = time;
	arq.seekg(pos2, arq.beg);
	arq.read((char*)&time, sizeof(Time));
	arqEscrita.seekp(pos1, arq.beg);
	arqEscrita.write((char*)&time, sizeof(time));
	arqEscrita.close();
	arqEscrita.open(nomeArquivo, fstream::out | fstream::in | fstream::binary);
	arqEscrita.seekp(pos2, arq.beg);
	arqEscrita.write((char*)&aux, sizeof(time));

	arq.close();
	arqEscrita.close();

}
void deletarTime() {

	ifstream arq(nomeArquivo);

	ofstream arqEscrita(nomeArquivo, fstream::out | fstream::in);
	string nomeTime;
	cout << "Escolha o time a ser deletado:" << endl;
	cin >> nomeTime;
	Time time;
	int posicaoInicioTime = 0;
	while (arq.read((char*)&time, sizeof(Time)))
	{
		if (time.nome == nomeTime) {
			arqEscrita.seekp(posicaoInicioTime);//aponta o ponteiro de escrita para a posicao desejada
			arqEscrita.write((char*)&"\0", sizeof(Time));
		}
		posicaoInicioTime = arq.tellg();//arq.tellg() pega a posiçao da ultima leitura
	}
	arq.close();
}