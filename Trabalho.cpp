// Trabalho.cpp : Este arquivo contém a função 'main'. A execução do programa começa e termina ali.
// Feito Por: Arthur Lucas Bosco Cunha e Castro e Joao Victor Oliveira
//GITHUB: https://github.com/arthur-lucas-castro/trabalho_ufla_ialg

#include <iostream>
#include <fstream>  
#include <sstream>
#include <vector>
#include <iomanip>
using namespace std;
//struct
struct Time
{
	char nome[15];
	int pontos;
	int vitorias;
	int derrotas;
	int empates;
};

//constantes

const int ORDENAR_POR_VITORIA = 1;
const int ORDENAR_POR_DERROTAS = 2;
const int ORDENAR_POR_EMPATES = 3;
const int ORDENAR_POR_NOME = 4;
const string NOME_ARQUIVO = "listaTimes.dat";
const string CARACTERES_INVALIDOS = ".,/ ";


//Voids
void EditarCampo(int escolhaUsuario, int posicaoTime, Time time, vector<int> posicoesTodosItens);
void InserirTime();
void ListarTimes();
void EditarTime();
void QuickSort(vector<int> posicoesTodosItens, int inicio, int final);
void Trocar(int pos1, int pos2);
void DeletarTime();
void MenuBusca();
void TrocarVirtual(int* pos1, int* pos2);
void QuickSortVirtual(vector<int> &posicoesTodosItens, int inicio, int final, int chaveOrdenacao);
void ExibirInformacoesAdicionais();
void PrintarLinhaTabela(Time time, int posicao);
void PrintarHeaderTabela();

//Ints
int Particionar(vector<int> posicoesTodosItens, int inicio, int final);
int ParticionarVirtual(vector<int>& posicoesTodosItens, int inicio, int final, int chaveOrdenacao);
int EscolherTipoOrdenacao(vector<int>& posicoesTodosItens, Time time, Time timePivo, int chaveOrdenacao, int index, int j);

//Strings
string& TrimFinal(string& stringTrim);

//Vectors
vector<int> getAllposicoes();

//Generic
template <typename Type>
Type tratarInput(Type& item);

//Time
Time buscaTimePorNome(string nomePesquisado, int& posicaoEncotrado, vector<int> posicoesTodosItens);
Time buscaTimePorPontuacao(int pontuacao, int& posicaoEncotrado, vector<int> posicoesTodosItens);
Time buscaTimePorVitoria(int vitorias, int& posicaoEncotrado, vector<int> posicoesTodosItens);



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
		cout << "5. Estatisticas do campeonato" << endl;
		cout << "6. Buscar time" << endl;
		cout << "7. Sair do programa" << endl;
		escolhaDoQueFazer = tratarInput(escolhaDoQueFazer);
		switch (escolhaDoQueFazer) {
		case(1):
			InserirTime();
			break;
		case(2):
			ListarTimes();
			break;
		case(3):
			EditarTime();
			break;
		case(4):
			DeletarTime();
			break;
		case(5):
			ExibirInformacoesAdicionais();
			break;
		case(6):
			MenuBusca();
			break;
		case(7):
			repetir = false;
			break;
		default:
			repetir = false;
			cout << "Escolha inválida";
			break;
		}
	}
}

//MENUS

void InserirTime() {
	ifstream arqLeitura(NOME_ARQUIVO, fstream::binary);
	ofstream arqEscritaCasoHajaRegistroDeletado(NOME_ARQUIVO, fstream::out | fstream::in | fstream::binary);
	ofstream arqEscritaCasoNaoHajaRegistroDeletado(NOME_ARQUIVO, fstream::app | fstream::binary);
	bool encontrou = false;
	string nome;
	Time time, timePesquisa;
	int posicaoInicioTime = 0;

	cout << "Digite o nome do time:(Apenas 14 caracteres)"<<endl;
	cin.ignore();
	getline(cin, nome);
	TrimFinal(nome);
	strncpy_s(time.nome, nome.c_str(), 14);
	cout << "Digite o numero de vitorias:" << endl;
	time.vitorias = tratarInput(time.vitorias);
	cout << "Digite o numero de empates:" << endl;
	time.empates = tratarInput(time.empates);
	cout << "Digite o numero de derrotas:" << endl;
	time.derrotas = tratarInput(time.derrotas);
	time.pontos = (time.vitorias * 3) + time.empates;;


	while (arqLeitura.read((char*)&timePesquisa, sizeof(Time)) && !encontrou)
	{
		if (strlen(timePesquisa.nome) == 0) {
			arqEscritaCasoHajaRegistroDeletado.seekp(posicaoInicioTime);//aponta o ponteiro de escrita para a posicao desejada
			arqEscritaCasoHajaRegistroDeletado.write((char*)&time, sizeof(Time));
			encontrou = true;
		}
		posicaoInicioTime = arqLeitura.tellg();//arq.tellg() pega a posiçao da ultima leitura
	}
	if (encontrou == false)
		arqEscritaCasoNaoHajaRegistroDeletado.write((char*)&time, sizeof(Time));

	arqLeitura.close();
	arqEscritaCasoHajaRegistroDeletado.close();
	arqEscritaCasoNaoHajaRegistroDeletado.close();
	cout << "Inserido com Sucesso" << endl;

}
void ListarTimes() {
	ifstream arqLeitura(NOME_ARQUIVO,  fstream::binary);
	vector<int> todasPosicoes = getAllposicoes();
	Time time;
	int posicaoTime = 1, tamanhoArrayPosicaoTimes = todasPosicoes.size() - 1;

	QuickSort(todasPosicoes, arqLeitura.beg, tamanhoArrayPosicaoTimes);
	PrintarHeaderTabela();
	while (arqLeitura.read((char*)&time, sizeof(Time)))
	{
		if (strlen(time.nome) > 0) {
			PrintarLinhaTabela(time, posicaoTime);
			posicaoTime++;
		}
		
	}
	arqLeitura.close();
}
void EditarTime() {

	Time timeEncontrado;
	string nome;
	vector<int> todasPosicoes = getAllposicoes();
	int escolhaDoQueFazer, posicaoInicioTime = 0, tamanhoArrayPosicaoTimes = todasPosicoes.size() - 1;
	cout << "Digite o nome do Time que deseja editar:" << endl;
	cin.ignore();
	getline(cin, nome);
	TrimFinal(nome);
	QuickSortVirtual(todasPosicoes, 0, tamanhoArrayPosicaoTimes, ORDENAR_POR_NOME);
	timeEncontrado = buscaTimePorNome(nome, posicaoInicioTime, todasPosicoes);
	if (posicaoInicioTime < 0) {
		cout << "Desculpe nao encontramos o time desejado:" << endl;
		return;
	}
	cout << "Encontramos o time desejado, Atualmente essa é a situaçao dele:" << endl;

	PrintarHeaderTabela();
	PrintarLinhaTabela(timeEncontrado, 0);

	cout << "Agora escolha o que voce vai editar: " << endl;
	cout << "1. Nome." << endl;
	cout << "2. Vitorias." << endl;
	cout << "3. Empates." << endl;
	cout << "4. Derrotas." << endl;
	cout << "0. Voltar" << endl;
	escolhaDoQueFazer = tratarInput(escolhaDoQueFazer);
	if (escolhaDoQueFazer < 0 || escolhaDoQueFazer > 4) {
		cout << "Opcao nao existe";
		return;
	}
	EditarCampo(escolhaDoQueFazer, posicaoInicioTime, timeEncontrado, getAllposicoes());
	cout << "Editado com Sucesso" << endl;
}
void EditarCampo(int escolhaUsuario, int posicaoTime, Time time, vector<int> posicoesTodosItens) {
	int tamanhoArrayPosicaoTimes = posicoesTodosItens.size() - 1;
	ofstream arqEscrita(NOME_ARQUIVO, fstream::out | fstream::in | fstream::binary);
	switch (escolhaUsuario)
	{
	case 1:
		arqEscrita.seekp(posicaoTime);//aponta o ponteiro de escrita para a posicao desejada
		cout << "Digite o novo nome do time:" << endl;
		cin >> time.nome;
		arqEscrita.write((char*)&time, sizeof(Time));
		arqEscrita.close();
		break;
	case 2:
		arqEscrita.seekp(posicaoTime);//aponta o ponteiro de escrita para a posicao desejada
		cout << "Digite o novo numero de vitorias do time:" << endl;
		time.vitorias = tratarInput(time.vitorias);
		time.pontos = (time.vitorias * 3) + time.empates;
		arqEscrita.write((char*)&time, sizeof(Time));
		arqEscrita.close();	
		QuickSort(posicoesTodosItens, arqEscrita.beg, tamanhoArrayPosicaoTimes);
		break;
	case 3:
		arqEscrita.seekp(posicaoTime);//aponta o ponteiro de escrita para a posicao desejada
		cout << "Digite o novo numero de empates do time:" << endl;
		time.empates = tratarInput(time.empates);
		time.pontos = (time.vitorias * 3) + time.empates;
		arqEscrita.write((char*)&time, sizeof(Time));
		arqEscrita.close();
		QuickSort(posicoesTodosItens, arqEscrita.beg, tamanhoArrayPosicaoTimes);
		break;
	case 4:
		arqEscrita.seekp(posicaoTime);//aponta o ponteiro de escrita para a posicao desejada
		cout << "Digite o novo numero de derrotas do time:" << endl;
		time.derrotas = tratarInput(time.derrotas);
		arqEscrita.write((char*)&time, sizeof(Time));
		arqEscrita.close();
		break;
	default:
		arqEscrita.close();
		break;
	}
}
void DeletarTime() 
{
	ofstream arqEscrita(NOME_ARQUIVO, fstream::out | fstream::in);
	string nomeTime;
	Time time;
	vector<int> todasPosicoes = getAllposicoes();
	int posicaoInicioTime = 0, tamanhoArrayPosicaoTimes = todasPosicoes.size()-1;
	
	bool encontrou = false;

	cout << "Escolha o time a ser deletado:" << endl;
	cin.ignore();
	getline(cin, nomeTime);
	TrimFinal(nomeTime);

	QuickSortVirtual(todasPosicoes, 0, tamanhoArrayPosicaoTimes, ORDENAR_POR_NOME);
	time = buscaTimePorNome(nomeTime, posicaoInicioTime, todasPosicoes);

	if (posicaoInicioTime < 0) {
		cout << "Desculpe nao encontramos o time desejado:" << endl;
		return;
	}
	arqEscrita.seekp(posicaoInicioTime);//aponta o ponteiro de escrita para a posicao desejada
	Time *timeNull = nullptr;
	arqEscrita.write((char*)&timeNull, sizeof(Time));
	arqEscrita.close();
	cout << "Deletado com Sucesso" << endl;
}
void ExibirInformacoesAdicionais() {// melhor identacao;
	int opcaoEscolhida;
	cout << "Estatiscas do campeonato. Qual voce deseja escolher" << endl;
	cout << "1. Tabela por vitorias" << endl;
	cout << "2. Tabela por derrotas" << endl;
	cout << "3. Tabela por empates" << endl;
	cout << "4. Tabela por ordem alfabetica" << endl;
	cout << "0. Voltar" << endl;
	opcaoEscolhida = tratarInput(opcaoEscolhida);
	if (opcaoEscolhida < 0 || opcaoEscolhida > 4) {
		cout << "Opcao nao existe";
		return;
	}
	if (opcaoEscolhida == 0)
		return;
	vector<int> todasPosicoes = getAllposicoes();
	int tamanhoArrayPosicaoTimes = todasPosicoes.size() - 1;
	
	QuickSortVirtual(todasPosicoes, 0, tamanhoArrayPosicaoTimes, opcaoEscolhida);
	ifstream arq(NOME_ARQUIVO, fstream::binary);
	Time time;

	PrintarHeaderTabela();
	for (int i = 0; i < tamanhoArrayPosicaoTimes+1; i++) {
		arq.seekg(todasPosicoes[i]);
		arq.read((char*)&time, sizeof(Time));
		if (strlen(time.nome) > 0) 
			PrintarLinhaTabela(time, i + 1);
		else 
			i--;
	}
	arq.close();
}
void MenuBusca() {

	int escolhaUsuario;
	cout << "Escolha como sera sua busca:" << endl;
	cout << "1. Busca por Nome" << endl;
	cout << "2. Busca por Pontuacao:" << endl;
	cout << "3. Busca por numero de Vitorias:" << endl;
	cout << "0. Sair:" << endl;
	escolhaUsuario = tratarInput(escolhaUsuario);
	if (escolhaUsuario < 0 || escolhaUsuario > 4) {
		cout << "Opcao nao existe";
		return;
	}
	if (escolhaUsuario == 0)
		return;
	string nome;
	Time timeEncontrado;
	vector<int> todasPosicoes = getAllposicoes();
	int posicaoInicioTime = -1, pontos, tamanhoArrayPosicaoTimes = todasPosicoes.size() - 1;
	switch (escolhaUsuario)
	{
		case 1:		
			cout << "Digite o nome do Time que deseja buscar:" << endl;
			cin >> nome;
			QuickSortVirtual(todasPosicoes, 0, tamanhoArrayPosicaoTimes, ORDENAR_POR_NOME);
			timeEncontrado = buscaTimePorNome(nome, posicaoInicioTime, todasPosicoes);
			if (posicaoInicioTime == -1) {
				cout << "Time nao encontrado" << endl;
			}
			PrintarHeaderTabela();
			PrintarLinhaTabela(timeEncontrado, 1);
			break;
		case 2:
			int pontos;
			cout << "Digite a pontuaçao que deseja pesquisar: (apenas o primeiro time sera exibido)" << endl;
			cin >> pontos;
			timeEncontrado = buscaTimePorPontuacao(pontos, posicaoInicioTime, todasPosicoes);
			if (posicaoInicioTime == -1) {
				cout << "Time nao encontrado" << endl;
			}
			PrintarHeaderTabela();
			PrintarLinhaTabela(timeEncontrado, 1);
			break;
		case 3:	
			cout << "Digite a quantidade de vitorias que deseja pesquisar:(apenas o primeiro time sera exibido)" << endl;
			cin >> pontos;
			QuickSortVirtual(todasPosicoes, 0, tamanhoArrayPosicaoTimes, ORDENAR_POR_VITORIA);
			timeEncontrado = buscaTimePorPontuacao(pontos, posicaoInicioTime, todasPosicoes);
			if (posicaoInicioTime == -1) {
				cout << "Time nao encontrado" << endl;
				return;
			}
			PrintarHeaderTabela();
			PrintarLinhaTabela(timeEncontrado, 1);
			break;
	}
}




//BUSCA BINARIA
Time buscaTimePorNome(string nomePesquisado, int& posicaoEncotrado, vector<int> posicoesTodosItens)
{
	ifstream arqLeitura(NOME_ARQUIVO, fstream::binary);
	Time time, timeEncontrado;
	int tamanhoTodosTimes = posicoesTodosItens.size() - 1;
	int inicio = 0, fim = tamanhoTodosTimes, meio;
	bool encontrou = false;

	while (inicio <= fim && !encontrou)
	{
		meio = (inicio + fim) / 2;
		arqLeitura.seekg(posicoesTodosItens[meio]);
		arqLeitura.read((char*)&time, sizeof(Time));

		if (strcmp(nomePesquisado.c_str(), time.nome) > 0)
		{
			inicio = meio + 1;
		}
		else if (strcmp(nomePesquisado.c_str(), time.nome) < 0)
		{
			fim = meio - 1;
		}
		else {
			posicaoEncotrado = posicoesTodosItens[meio];
			encontrou = true;
			return time;
		}
	}
	if (!encontrou) {
		posicaoEncotrado = -1;
		return time;
	}
}
Time buscaTimePorPontuacao(int pontuacao, int& posicaoEncotrado, vector<int> posicoesTodosItens) {

	ifstream arqLeitura(NOME_ARQUIVO, fstream::binary);
	Time time;
	int tamanhoTodosTimes = posicoesTodosItens.size() - 1;

	int inicio = 0, fim = tamanhoTodosTimes, meio;
	bool encontrou = false;
	int ultimaOperacao = 0;
	while (inicio <= fim)
	{
		meio = (inicio + fim) / 2;
		arqLeitura.seekg(posicoesTodosItens[meio]);
		arqLeitura.read((char*)&time, sizeof(Time));

		if (pontuacao < time.pontos)
		{
			inicio = meio + 1;
			ultimaOperacao = 1;
		}
		else if (pontuacao > time.pontos)
		{
			fim = meio - 1;
			ultimaOperacao = -1;
		}
		else {
			posicaoEncotrado = posicoesTodosItens[meio];
			encontrou = true;
			return time;
		}
	}
	if (!encontrou) {
		posicaoEncotrado = -1;
		return time;
	}

}
Time buscaTimePorVitoria(int vitorias, int& posicaoEncotrado, vector<int> posicoesTodosItens) {

	ifstream arqLeitura(NOME_ARQUIVO, fstream::binary);
	Time time;
	int tamanhoTodosTimes = posicoesTodosItens.size() - 1;
	int inicio = 0, fim = tamanhoTodosTimes, meio;
	bool encontrou = false;
	while (inicio <= fim)
	{
		meio = (inicio + fim) / 2;
		arqLeitura.seekg(posicoesTodosItens[meio]);
		arqLeitura.read((char*)&time, sizeof(Time));

		if (vitorias < time.vitorias)
		{
			inicio = meio + 1;
		}
		else if (vitorias > time.vitorias)
		{
			fim = meio - 1;
		}
		else {
			posicaoEncotrado = posicoesTodosItens[meio];
			encontrou = true;
			return time;
		}
	}
	if (!encontrou) {
		posicaoEncotrado = -1;
		return time;
	}

}

//ORDENACAO
//QUICKSORT ORDENANDO ARQUIVO
void QuickSort(vector<int> posicoesTodosItens, int inicio, int final) {
	if (inicio < final)
	{
		int pi = Particionar(posicoesTodosItens, inicio, final);
		QuickSort(posicoesTodosItens, inicio, pi - 1);
		QuickSort(posicoesTodosItens, pi + 1, final);
	}
}
int Particionar(vector<int> posicoesTodosItens, int inicio, int final)
{
	Time time, timePivo;
	ifstream arqLeitura(NOME_ARQUIVO, fstream::binary);
	arqLeitura.seekg(posicoesTodosItens[final], arqLeitura.beg);
	arqLeitura.read((char*)&time, sizeof(Time));
	timePivo = time;

	int i = (inicio - 1);
	for (int j = inicio; j <= final - 1; j++)
	{
		arqLeitura.seekg(posicoesTodosItens[j], arqLeitura.beg);
		arqLeitura.read((char*)&time, sizeof(Time));
		if (time.pontos >= timePivo.pontos)
		{
			if (time.pontos == timePivo.pontos) {
				if (time.vitorias > timePivo.vitorias) {
					i++;
					Trocar(posicoesTodosItens[i], posicoesTodosItens[j]);
				}
			}
			else {
				i++;
				Trocar(posicoesTodosItens[i], posicoesTodosItens[j]);
			}
		}
	}
	Trocar(posicoesTodosItens[i + 1], posicoesTodosItens[final]);
	arqLeitura.close();
	return (i + 1);
}
void Trocar(int pos1, int pos2)
{
	ofstream arqEscrita(NOME_ARQUIVO, fstream::out | fstream::in | fstream::binary);
	ifstream arqLeitura(NOME_ARQUIVO);
	Time time, timeAux;
	arqLeitura.seekg(pos1, arqLeitura.beg);
	arqLeitura.read((char*)&time, sizeof(Time));
	timeAux = time;

	arqLeitura.seekg(pos2, arqLeitura.beg);
	arqLeitura.read((char*)&time, sizeof(Time));
	arqEscrita.seekp(pos1, arqLeitura.beg);
	arqEscrita.write((char*)&time, sizeof(time));

	arqEscrita.close();
	arqEscrita.open(NOME_ARQUIVO, fstream::out | fstream::in | fstream::binary);

	arqEscrita.seekp(pos2, arqLeitura.beg);
	arqEscrita.write((char*)&timeAux, sizeof(time));
	arqLeitura.close();
	arqEscrita.close();

}
//QUICKSORT ORDENANDO ARRAY DE POSICOES PARA LEITURA
void QuickSortVirtual(vector<int>& posicoesTodosItens, int inicio, int final, int chaveOrdenacao) {
	int pivo = 0;
	if (inicio < final)
	{
		pivo = ParticionarVirtual(posicoesTodosItens, inicio, final, chaveOrdenacao);
		QuickSortVirtual(posicoesTodosItens, inicio, pivo - 1, chaveOrdenacao);
		QuickSortVirtual(posicoesTodosItens, pivo + 1, final, chaveOrdenacao);

	}
}
int ParticionarVirtual(vector<int>& posicoesTodosItens, int inicio, int final, int chaveOrdenacao)
{
	Time time;
	ifstream arq(NOME_ARQUIVO, fstream::binary);
	int size = sizeof(Time);
	arq.seekg(posicoesTodosItens[final], arq.beg);

	arq.read((char*)&time, sizeof(Time));
	Time timePivo = time;
	int i = (inicio - 1);

	for (int j = inicio; j <= final - 1; j++)
	{
		arq.seekg(posicoesTodosItens[j], arq.beg);

		arq.read((char*)&time, sizeof(Time));
		i = EscolherTipoOrdenacao(posicoesTodosItens, time, timePivo, chaveOrdenacao, i, j);

	}
	TrocarVirtual(&posicoesTodosItens[i + 1], &posicoesTodosItens[final]);
	arq.close();
	return (i + 1);

}
int EscolherTipoOrdenacao(vector<int>& posicoesTodosItens, Time time, Time timePivo, int chaveOrdenacao, int index, int j) {
	switch (chaveOrdenacao)
	{
		case ORDENAR_POR_VITORIA:
			if (time.vitorias >= timePivo.vitorias)
			{
				if (time.vitorias == timePivo.vitorias) {
					if (time.pontos > timePivo.pontos) {
						index++;
						TrocarVirtual(&posicoesTodosItens[index], &posicoesTodosItens[j]);
					}
				}
				else {
					index++;
					TrocarVirtual(&posicoesTodosItens[index], &posicoesTodosItens[j]);
				}
			}
			break;
		case ORDENAR_POR_DERROTAS:
			if (time.derrotas >= timePivo.derrotas)
			{
				if (time.derrotas == timePivo.derrotas) {
					if (time.pontos > timePivo.pontos) {
						index++;
						TrocarVirtual(&posicoesTodosItens[index], &posicoesTodosItens[j]);
					}
				}
				else {
					index++;
					TrocarVirtual(&posicoesTodosItens[index], &posicoesTodosItens[j]);
				}
			}
			break;
		case ORDENAR_POR_EMPATES:
			if (time.empates >= timePivo.empates)
			{
				if (time.empates == timePivo.empates) {
					if (time.pontos > timePivo.pontos) {
						index++;
						TrocarVirtual(&posicoesTodosItens[index], &posicoesTodosItens[j]);
					}
				}
				else {
					index++;
					TrocarVirtual(&posicoesTodosItens[index], &posicoesTodosItens[j]);
				}
			}
			break;
		case ORDENAR_POR_NOME:
			if (strcmp(time.nome, timePivo.nome) <= 0)
			{
				if (time.nome == timePivo.nome) {
					if (time.pontos > timePivo.pontos) {
						index++;
						TrocarVirtual(&posicoesTodosItens[index], &posicoesTodosItens[j]);
					}
				}
				else {
					index++;
					TrocarVirtual(&posicoesTodosItens[index], &posicoesTodosItens[j]);
				}
			}
			break;
	}
	return index;
}
void TrocarVirtual(int* posicao1, int* posicao2)
{
	int aux = *posicao1;
	*posicao1 = *posicao2;
	*posicao2 = aux;
}

//UTEIS
void PrintarHeaderTabela() {
	cout << '|' << setw(15) << "POSICAO" << '|' << setw(15) << "NOME" << '|' << setw(15) << "PONTOS" << '|' << setw(15) << "VITORIAS" << '|' << setw(15) << "EMPATES" << '|' << setw(15) << "DERROTAS" << '|' << endl;
	cout << '|' << "---------------" << '|' << "---------------" << '|' << setw(15) << "---------------" << '|' << setw(15) << "---------------" << '|' << setw(15) << "---------------" << '|' << setw(15) << "---------------" << "|" << endl;
}
void PrintarLinhaTabela(Time time, int posicao) {
	cout << '|' << setw(15) << posicao << '|' << setw(15) << time.nome << '|' << setw(15) << time.pontos << '|' << setw(15) << time.vitorias << '|' << setw(15) << time.empates << '|' << setw(15) << time.derrotas << '|' << endl;
	cout << '|' << setw(15) << "---------------" << '|' << "---------------" << '|' << setw(15) << "---------------" << '|' << setw(15) << "---------------" << '|' << setw(15) << "---------------" << '|' << setw(15) << "---------------" << "|" << endl;
}
string& TrimFinal(string& stringTrim)
{
	stringTrim.erase(stringTrim.find_last_not_of(CARACTERES_INVALIDOS) + 1);
	return stringTrim;
}
vector<int> getAllposicoes() {
	ifstream arqLeitura(NOME_ARQUIVO, fstream::binary);
	Time time;
	vector<int> posicoes;
	int posicaoInicioTime = 0;
	while (arqLeitura.read((char*)&time, sizeof(Time)))
	{
		if (strlen(time.nome) > 0) {
			posicoes.push_back(posicaoInicioTime);
		}
		posicaoInicioTime = arqLeitura.tellg();//arq.tellg() pega a posiçao da ultima leitura
	}
	return posicoes;
}
template <typename Type>
Type tratarInput(Type& item) {
	cin >> item;
	while (cin.fail())
	{
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Valor invalido, insira novamente" << endl;
		cin >> item;
	}
	return item;
}
