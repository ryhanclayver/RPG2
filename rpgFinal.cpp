#include <iostream>
#include <vector>
#include <conio.h>
#include <windows.h>
#include<iomanip>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;


// Booleanos para utilizar no if de combate contra Boss para não lutar contra o Boss novamente
// Após já tê-los derrotado
bool gu = true;
bool cl = true;
bool la = true;
bool br = true;

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

// Classe de Personagem
class Personagem {
protected:
    string nome, classe;
    int pv, pa, pd, pvOriginal, paOriginal;
    int danoTotalCausado;
    std::vector<std::string> inventario;

public:
    Personagem(const string& nome, const string& classe, int pv, int pa, int pd)
        : nome(nome), classe(classe), pv(pv), pa(pa), pd(pd), danoTotalCausado(0), pvOriginal(pv), paOriginal(pa) {}

    void receberDano(int dano) {
        if (dano > 0) {
            pv -= dano;
            if (pv < 0) {
                pv = 0;
            }
        }
    }

    void adicionarAoInventario(const std::string& item) {
        inventario.push_back(item);
    }

    void exibirInventario() const {
        if (inventario.empty()) {
            std::cout << "O inventário está vazio." << std::endl;
        } else {
            std::cout << "Inventário:" << std::endl;
            for (const auto& item : inventario) {
                std::cout << "- " << item << std::endl;
            }
        }
    }

    void resetarAtributos() {
        pv = pvOriginal;
    }

    string getNome() const {
        return nome;
    }

    string getClasse() const {
        return classe;
    }

    int getPV() const {
        return pv;
    }

    int getPA() const {
        return pa;
    }

    int getPD() const {
        return pd;
    }

    void setPV(int novoPV) {
        pvOriginal = novoPV;
        pv = pvOriginal;
    }

    void setPD(int novoPD) {
        pd = novoPD;
    }

    void setPA(int novoPA){
        pa = novoPA;
    }

    void adicionarDanoCausado(int dano) {
        if (dano > 0) {
            danoTotalCausado += dano;
        }
    }
};


class JogoRPG {
    protected:

    public:
        JogoRPG() {}

    void iniciarCombate(Personagem* personagem1, Personagem* personagem2) {
        int rounds = 0;

        while (personagem1->getPV() > 0 && personagem2->getPV() > 0) {
            cout << "\t\nRound: " << rounds + 1 << endl;
            cout << "Vida de "<< personagem1->getNome()<<": " << personagem1->getPV() << " pontos." << endl;
            cout << "Vida de "<< personagem2->getNome()<<": " << personagem2->getPV() << " pontos." << endl;
            cout << endl;
            rounds++;

            int danospersonagem1 = personagem1->getPA() - personagem2->getPD();
            int danospersonagem2 = personagem2->getPA() - personagem1->getPD();

            if (danospersonagem1 > 0) {
                personagem2->receberDano(danospersonagem1);
                cout << "Perda de vida de " << personagem2->getNome() << ": " << danospersonagem1 << " pontos." << endl;
                personagem1->adicionarDanoCausado(danospersonagem1);
            }
            else {
                cout << "O ataque de " << personagem1->getNome() << " não causou dano a " << personagem2->getNome() << "." << endl;
            }
            if (danospersonagem2 > 0) {
                personagem1->receberDano(danospersonagem2);
                cout << "Perda de vida de " << personagem1->getNome() << ": " << danospersonagem2 << " pontos." << endl;
                personagem2->adicionarDanoCausado(danospersonagem2);
            }
            else {
                cout << "O ataque de " << personagem2->getNome() << " não causou dano a " << personagem1->getNome() << "." << endl;
            }

            if (personagem1->getPV() <= 0 || personagem2->getPV() <= 0) {
                cout << "\n\t\tO combate terminou!\n" << endl;
                break;
            }
            system("pause");
        }

        if (personagem1->getPV() <= 0 && personagem2->getPV() > 0) {
            system("cls");
            cout << "\t\t" << personagem1->getNome() << " perdeu!" << endl;
            cout << "\t\t Game Over" << endl; 
            system("pause"); 
            exit(1); // Fecha o programa porque jogador perdeu
        }
        else if (personagem2->getPV() <= 0 && personagem1->getPV() > 0) {
            system("cls");
            cout << "\t\t" << personagem1->getNome() << " venceu!" << endl;
            system("pause");
            personagem1->resetarAtributos();  // Reabastecer pontos de vida
        }
    }
};

class Bruxo : public Personagem { //causar dano e se curar com metade desse dano causado
//Drenagem vital - ataca e se cura e causa sangramento
public:
    Bruxo(const string& nome)
        : Personagem(nome, "Bruxo", gerarPV(), gerarPA(), gerarPD()) {}

private:
    int gerarPV() {
        return rand() % (90 - 70 + 1) + 70;
    }

    int gerarPA() {
        return rand() % (35 - 15 + 1) + 15;
    }

    int gerarPD() {
        return rand() % (15 - 10 + 1) + 10;
    }
};

class Mago : public Personagem { // causar dano alto (maior que o bruxo pra compensar que ele nao se cura)
//Explosão arcana - explosão de dano
public:
    Mago(const string& nome)
        : Personagem(nome, "Mago", gerarPV(), gerarPA(), gerarPD()) {}

private:
    int gerarPV() {
        return rand() % (90 - 70 + 1) + 70;
    }

    int gerarPA() {
        return rand() % (25 - 10 + 1) + 10;
    }

    int gerarPD() {
        return rand() % (20 - 15 + 1) + 15;
    }
};

class Guerreiro : public Personagem { // aumenta os atributos de ataque e vida
//Frenesi de batalha - aumenta seus atributos de ataque e defesa
public:
    Guerreiro(const string& nome)
        : Personagem(nome, "Guerreiro", gerarPV(), gerarPA(), gerarPD()) {}

private:
    int gerarPV() {
        return rand() % (100 - 80 + 1) + 80;
    }

    int gerarPA() {
        return rand() % (25 - 10 + 1) + 10;
    }

    int gerarPD() {
        return rand() % (20 - 10 + 1) + 10;
    }
};

class Druida : public Personagem { // ganha escudo
//ataque elemental - ataque com mais chance de sangramento
public:
    Druida(const string& nome)
        : Personagem(nome, "Druida", gerarPV(), gerarPA(), gerarPD()) {}

private:
    int gerarPV() {
        return rand() % (100 - 90 + 1) + 90;
    }

    int gerarPA() {
        return rand() % (30 - 20 + 1) + 20;
    }

    int gerarPD() {
        return rand() % (20 - 10 + 1) + 10;
    }
};

class Clerigo : public Personagem { // se cura
//Ascensão celestial - cura em si
public:
    Clerigo(const string& nome)
        : Personagem(nome, "Clerigo", gerarPV(), gerarPA(), gerarPD()) {}

private:
    int gerarPV() {
        return rand() % (90 - 75 + 1) + 75;
    }

    int gerarPA() {
        return rand() % (20 - 15 + 1) + 15;
    }

    int gerarPD() {
        return rand() % (20 - 15 + 1) + 10;
    }
};

class Ladino : public Personagem { // causa dano alto e tem chance de causar sangramento
 //Sombra mortal - dano massivo e sangramento
public:
    Ladino(const string& nome)
        : Personagem(nome, "Ladino", gerarPV(), gerarPA(), gerarPD()) {}

private:
    int gerarPV() {
        return rand() % (90 - 70 + 1) + 70;
    }

    int gerarPA() {
        return rand() % (25 - 15 + 1) + 15;
    }

    int gerarPD() {
        return rand() % (20 - 15 + 1) + 10;
    }
};

Personagem* criarPersonagem() {
    string nome, classe;
    cout << "Digite o nome do personagem: ";
    getline(cin, nome);

    cout << "Escolha a classe do personagem (Bruxo, Mago, Guerreiro, Druida, Clerigo, Ladino): ";
    getline(cin, classe);

    if (classe == "Bruxo") {
        return new Bruxo(nome);
    } else if (classe == "Mago") {
        return new Mago(nome);
    } else if (classe == "Guerreiro") {
        return new Guerreiro(nome);
    } else if (classe == "Druida") {
        return new Druida(nome);
    } else if (classe == "Clerigo") {
        return new Clerigo(nome);
    } else if (classe == "Ladino") {
        return new Ladino(nome);
    } else {
        cout << "Classe inválida. Criando personagem padrão." << endl;
        return new Personagem(nome, "Desconhecida", 100, 10, 10);
    }
}

int main() {
    // Definindo a codificação de caracteres para UTF-8
    SetConsoleOutputCP(CP_UTF8);
    srand(static_cast<unsigned>(time(nullptr)));

    //Criando o Jogo
    JogoRPG jogo;

    // Criando bosses usando as classes existentes
    Personagem* boss1 = new Clerigo("Clerigo");
    Personagem* boss2 = new Guerreiro("Guerreiro");
    Personagem* boss3 = new Ladino("Ladino");
    Personagem* boss4 = new Bruxo("Bruxo");

    // Criando Personagem
    Personagem* personagem1 = criarPersonagem();
    
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
    system("cls");  // Limpar o terminal

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
        system("cls");
        cout << "Você pega a Chave Misteriosa do seu inventário..." << endl << endl;
        cout << "Coloca na tranca..." << endl << endl;
        cout << "Roda a maçaneta..." << endl << endl;
        cout << "A porta se abre" << endl << endl;
        cout << "Parabéns! Você saiu do labirinto e ganhou o jogo!" << endl;
        break; // Encerrar o loop se o jogador venceu
    }

    // Combate contra Boss
    if (playerPosI == 12 && playerPosJ == 1 && (cl == true)) { // Posição do Boss 1 (Clerigo)
        system("cls");  // Limpar o terminal
        jogo.iniciarCombate(personagem1, boss1);
        cout << "Você derrotou o Clerigo e ganhou uma Poção de Vigor!" << endl << endl;
        system("pause");
        personagem1->adicionarAoInventario("Poção de Vigor");

        personagem1->setPV(personagem1->getPV() + 10); // Aumentando pontos de vida
        cout << endl << "Agora você possui " << personagem1->getPV() << " pontos de vida " << endl;
        cl = false;
        system("pause");

        } if (playerPosI == 12 && playerPosJ == 11 && (gu == true)) { // Posição do Boss 2 (Guerreiro)
        system("cls");  // Limpar o terminal
        jogo.iniciarCombate(personagem1, boss2);
        cout << "Você derrotou o Guerreiro e ganhou uma Armadura!" << endl << endl;
        system("pause");
        personagem1->adicionarAoInventario("Armadura");

        if (gu) {  // Certifica-se de adicionar a armadura apenas uma vez
            personagem1->setPD(personagem1->getPD() + 2); // Aumentando armadura
            cout << endl << "Agora você possui " << personagem1->getPD() << " pontos de defesa" << endl;
            gu = false;
            system("pause");
        }
    } else if (playerPosI == 12 && playerPosJ == 23 && (la == true)) { // Posição do Boss 3 (Ladino)
        system("cls");  // Limpar o terminal
        jogo.iniciarCombate(personagem1, boss3);
        cout << "Você derrotou o Ladino e ganhou uma Adaga!" << endl << endl;
        system("pause");
        personagem1->adicionarAoInventario("Adaga");
        personagem1->setPA(personagem1->getPA() + 2); // Aumentando ataque
        cout << endl << "Agora você possui " << personagem1->getPA() << " pontos de ataque" << endl;
        la = false;
        system("pause");
        
    } else if (playerPosI == 12 && playerPosJ == 33 && (br == true)) { // Posição do Boss 4 (Bruxo)
        system("cls");  // Limpar o terminal
        jogo.iniciarCombate(personagem1, boss4);
        cout << "Você derrotou o Bruxo e ganhou uma Chave Misteriosa!" << endl << endl;
        personagem1->adicionarAoInventario("Chave Misteriosa");
        br = false;
        system("pause");
    }
}
    delete personagem1;
    delete boss1;
    delete boss2;
    delete boss3;
    delete boss4;

    return 0;
}
