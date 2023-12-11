#include <iostream>
#include <vector>
#include <conio.h>
#include <windows.h>

using namespace std;

// Definindo o tamanho do mapa
const int linhas = 24;
const int colunas = 36;

// Função para imprimir o mapa
void imprimirMapa(const vector<vector<char>>& mapa, int playerPosI, int playerPosJ) {
    system("cls");

    for (int i = 0; i < linhas; ++i) {
        for (int j = 0; j < colunas; ++j) {
            if (i == playerPosI && j == playerPosJ) {
                cout << 'P' << " ";
            } else {
                cout << mapa[i][j] << " ";
            }
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

    //Criando Boss
    mapa[12][0] = 'C'; // Boss 1 Clerigo
    mapa[11][11] = 'G'; // Boss 2 Guerreiro
    mapa[11][23] = 'L'; // Boss 3 Ladino
    mapa[11][33] = 'B'; // Boss 4 Bruxo
}

// Função para criar um caminho dentro do labirinto da entrada até a saída
void criarCaminhoPrincipal(vector<vector<char>>& mapa) {
    for (int i = 1; i < linhas - 1; ++i) {
        mapa[i][1] = ' ';
    }

    for (int i = 1; i < linhas - 1; ++i) {
        mapa[i][colunas - 2] = ' ';
    }

    for (int j = 2; j < colunas - 2; ++j) {
        mapa[linhas / 2][j] = ' ';
    }
}

int main() {
    // Definindo a codificação de caracteres para UTF-8
    SetConsoleOutputCP(CP_UTF8);
    
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

    int playerPosI = 1;
    int playerPosJ = 1;

while (true) {
    imprimirMapa(mapa, playerPosI, playerPosJ);

    // Capturar tecla de seta
    int tecla = _getch();

    // Mover o jogador
    switch (tecla) {
        case 72: // Tecla de seta para cima
            if (playerPosI > 1 && mapa[playerPosI - 1][playerPosJ] != '1') {
                playerPosI--;
            }
            break;
        case 80: // Tecla de seta para baixo
            if (playerPosI < linhas - 2 && mapa[playerPosI + 1][playerPosJ] != '1') {
                playerPosI++;
            }
            break;
        case 75: // Tecla de seta para a esquerda
            if (playerPosJ > 1 && mapa[playerPosI][playerPosJ - 1] != '1') {
                playerPosJ--;
            }
            break;
        case 77: // Tecla de seta para a direita
            if (playerPosJ < colunas - 2 && mapa[playerPosI][playerPosJ + 1] != '1') {
                playerPosJ++;
            }
            break;
        default:
            break;
    }

    // Verificar se o jogador chegou à saída
    if (playerPosI == linhas - 2 && playerPosJ == colunas - 2) {
        cout << "Parabéns! Você saiu do labirinto e ganhou o jogo!" << endl;
        break; // Encerrar o loop se o jogador venceu
    }
}
    return 0;
}


