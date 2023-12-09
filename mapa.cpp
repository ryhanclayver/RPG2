#include <iostream>
#include <vector>

using namespace std;

// Definindo o tamanho do mapa
const int linhas = 24;
const int colunas = 36;

// Função para imprimir o mapa
void imprimirMapa(const vector<vector<char>>& mapa) {
    for (int i = 0; i < linhas; ++i) {
        for (int j = 0; j < colunas; ++j) {
            cout << mapa[i][j] << " ";
        }
        cout << endl;
    }
}

// Função para criar caminhos dentro do labirinto que não levam à saída
void criarCaminhosExtras(vector<vector<char>>& mapa) {
    // Caminho 1
    for (int i = 1; i < linhas / 3; ++i) {
        mapa[i][colunas / 3] = ' ';
    }

    // Caminho 2
    for (int i = linhas / 3; i < 2 * linhas / 3; ++i) {
        mapa[i][2 * colunas / 3] = ' ';
    }

    // Caminho 3
    for (int j = colunas / 3; j < 2 * colunas / 3; ++j) {
        mapa[2 * linhas / 3][j] = ' ';
    }

    // Conectando os caminhos
    for (int i = linhas / 3; i < 2 * linhas / 3; ++i) {
        mapa[i][colunas / 3] = ' ';
        mapa[i][2 * colunas / 3] = ' ';
    }

    // Caminho 4
    for (int j = 1; j < 12; ++j) {
        mapa[linhas / 2][j] = ' ';
    }

    // Conectando os caminhos
    for (int j = colunas / 3; j < 2 * colunas / 3; ++j) {
        mapa[linhas / 2][j] = ' ';
    }
}

// Função para criar um caminho dentro do labirinto da entrada até a saída
void criarCaminhoPrincipal(vector<vector<char>>& mapa) {
    for (int i = 1; i < linhas - 2; ++i) {
        mapa[i][1] = ' ';
    }

    for (int j = 2; j < colunas - 2; ++j) {
        mapa[linhas / 2][j] = ' ';
    }

    for (int i = linhas / 2; i < linhas - 2; ++i) {
        mapa[i][colunas - 2] = ' ';
    }
}

int main() {
    // Inicializando o mapa preenchendo todo o labirinto com '1'
    vector<vector<char>> mapa(linhas, vector<char>(colunas, '1'));

    // Adicionando borda superior e inferior
    for (int j = 0; j < colunas; ++j) {
        mapa[0][j] = mapa[linhas - 1][j] = '-';
    }

    // Adicionando borda esquerda e direita
    for (int i = 1; i < linhas - 1; ++i) {
        mapa[i][0] = mapa[i][colunas - 1] = '|';
    }

    // Adicionando entrada e saída
    mapa[1][0] = 'E';
    mapa[linhas - 2][colunas - 1] = 'S';

    // Criando caminhos dentro do labirinto que não levam à saída
    criarCaminhosExtras(mapa);

    // Criando um caminho dentro do labirinto da entrada até a saída
    criarCaminhoPrincipal(mapa);

    // Imprimindo o mapa
    imprimirMapa(mapa);

    return 0;
}