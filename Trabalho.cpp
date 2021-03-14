// Trabalho.cpp : Este arquivo contém a função 'main'. A execução do programa começa e termina ali.
//

#include <iostream>
#include <fstream>  
#include <vector>
using namespace std;
struct Time
{
    string nome;
    int pontos;
    int vitorias;
    int derrotas;
    int empates;
};

void trocar(Time* a, Time* b);
int particionar(vector<Time>& vetor, int inicio, int final);
void quickSort(vector<Time>& vetor, int inicio, int final);
void criaArquivo();



int main()
{
	criaArquivo();
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

void quickSort(vector<Time>& vetor, int inicio, int final) {
    if (inicio < final)
    {
        int pi = particionar(vetor, inicio, final);
        quickSort(vetor, inicio, pi - 1);
        quickSort(vetor, pi + 1, final);
    }
}
int particionar(vector<Time>& vetor, int inicio, int final)
{
    int pivo = vetor[final].pontos;
    int i = (inicio - 1);

    for (int j = inicio; j <= final - 1; j++)
    {
        if (vetor[j].pontos <= pivo)
        {
            i++;
            trocar(&vetor[i], &vetor[j]);
        }
    }
    trocar(&vetor[i + 1], &vetor[final]);
    return (i + 1);
}
void trocar(Time* a, Time* b)
{
    Time aux = *a;
    *a = *b;
    *b = aux;
}