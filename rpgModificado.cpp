#include<iostream>
#include<iomanip>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

class Personagem {
protected:
    string nome, classe;
    int pv, pa, pd, pvOriginal, paOriginal;
    int danoTotalCausado;

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

    void resetarAtributos() {
        pv = pvOriginal;
        pa = paOriginal;
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
        rounds++;
        swap(personagem1, personagem2);

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
    }

    if (personagem1->getPV() <= 0 && personagem2->getPV() > 0) {
        cout << "\t\t" << personagem2->getNome() << " venceu!" << endl;
    }
    else if (personagem2->getPV() <= 0 && personagem1->getPV() > 0) {
        cout << "\t\t" << personagem1->getNome() << " venceu!" << endl;
    }
    else {
        int ataquePersonagem1 = personagem1->getPA();
        int ataquePersonagem2 = personagem2->getPA();
        int vidaPersonagem1 = personagem1->getPV();
        int vidaPersonagem2 = personagem2->getPV();

        if (ataquePersonagem1 > ataquePersonagem2) {
            cout << "\t\t" << personagem1->getNome() << " venceu!" << endl;
        }
        else if (ataquePersonagem2 > ataquePersonagem1) {
            cout << "\t\t" << personagem2->getNome() << " venceu!" << endl;
        }
        else {
            cout << "\t" << "O combate terminou sem um vencedor claro!" << endl;
        }
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
        return rand() % (35 - 25 + 1) + 25;
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
    srand(static_cast<unsigned>(time(nullptr)));

    Personagem* personagem1 = criarPersonagem();
    Personagem* personagem2 = criarPersonagem();

    JogoRPG jogo;
    jogo.iniciarCombate(personagem1, personagem2);

    delete personagem1;
    delete personagem2;

    return 0;
}
