//Bianca, Ryhan e Tauani
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
    vector<Personagem*> derrotados;

    static string gerarNomeAleatorio() {
        const string nomes[] = {"Alice", "Bob", "Charlie", "Pitty", "Frank", "David", "Emma", "Fiona", "George", "Hannah", "Isabel", "Abigail", "Katarina", "Morgana", "Laila", "Qiyana", "Veno", "Max", "Rick", "Josephine", "Marcu", "Harry", "Thomas", "Polly", "Ben", "Vegan", "Albert", "Oberon", "Lilith", "Thalia", "Zephyr", "Celestia", "Hecate", "Solstice", "Branwen", "Kaelthas", "Selene", "Orion", "Persephone", "Astra", "Asmodeus", "Calliope", "Elysium", "Melissandre", "Hercules"};
        return nomes[rand() % (sizeof(nomes) / sizeof(nomes[0]))];
    }

public:
    Personagem(const string& nome, const string& classe, int pv, int pa, int pd)
        : nome(gerarNomeAleatorio()), classe(classe), pv(pv), pa(pa), pd(pd), danoTotalCausado(0), pvOriginal(pv), paOriginal(pa) {}

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

    void adicionarDerrotado(Personagem* derrotado) {
        derrotados.push_back(derrotado);
    }

    int getDanoTotalCausado() const {
        return danoTotalCausado;
    }

    void adicionarDanoCausado(int dano) {
        if (dano > 0) {
            danoTotalCausado += dano;
        }
    }
};

class JogoRPG {
protected:
    vector<Personagem*> personagens;

public:
    JogoRPG() {}

    void adicionarPersonagem(Personagem* novoPersonagem) {
        personagens.push_back(novoPersonagem);
    }

    void iniciarCombate(Personagem* personagem1, Personagem* personagem2) {
        int rounds = 0;

        while (rounds < 10 && personagem1->getPV() > 0 && personagem2->getPV() > 0) {
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

            if (rounds == 10 || personagem1->getPV() <= 0 || personagem2->getPV() <= 0) {
                cout << "\n\t\tO combate terminou!\n" << endl;
                break;
            }
        }

        int danoTotalPersonagem1 = personagem1->getDanoTotalCausado();
        int danoTotalPersonagem2 = personagem2->getDanoTotalCausado();

if (rounds == 10 || personagem1->getPV() <= 0 || personagem2->getPV() <= 0) {
}

if (personagem1->getPV() <= 0 && personagem2->getPV() > 0) {
    personagem2->adicionarDerrotado(personagem1);
    cout << "\t\t" << personagem2->getNome() << " venceu!" << endl;
}
else if (personagem2->getPV() <= 0 && personagem1->getPV() > 0) {
    personagem1->adicionarDerrotado(personagem2);
    cout << "\t\t" << personagem1->getNome() << " venceu!" << endl;
}
else {
    int ataquePersonagem1 = personagem1->getPA();
    int ataquePersonagem2 = personagem2->getPA();
    int vidaPersonagem1 = personagem1->getPV();
    int vidaPersonagem2 = personagem2->getPV();

    if (ataquePersonagem1 > ataquePersonagem2) {
        cout << "\t\t" << personagem1->getNome() << " venceu!" << endl;
        personagem1->adicionarDerrotado(personagem2);
    }
    else if (ataquePersonagem2 > ataquePersonagem1) {
        cout << "\t\t" << personagem2->getNome() << " venceu!" << endl;
        personagem2->adicionarDerrotado(personagem1);
    }
    else {
        // Em caso de empate no ataque, ganha quem tiver mais vida
        if (vidaPersonagem1 > vidaPersonagem2) {
            cout << "\t\t" << personagem1->getNome() << " venceu!" << endl;
            personagem1->adicionarDerrotado(personagem2);
        }
        else if (vidaPersonagem2 > vidaPersonagem1) {
            cout << "\t\t" << personagem2->getNome() << " venceu!" << endl;
            personagem2->adicionarDerrotado(personagem1);
        }
        else {
            cout << "\t" << "O combate terminou em empate, sem vencedor!" << endl;
        }
    }
}

};

class Bruxo : public Personagem { //causar dano e se curar com metade desse dano causado
//Drenagem vital - ataca e se cura e causa sangramento
public:
    Bruxo()
        : Personagem(gerarNomeAleatorio(), "Bruxo", gerarPV(), gerarPA(), gerarPD()) {}

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
    Mago()
        : Personagem(gerarNomeAleatorio(), "Mago", gerarPV(), gerarPA(), gerarPD()) {}

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
    Guerreiro()
        : Personagem(gerarNomeAleatorio(), "Guerreiro", gerarPV(), gerarPA(), gerarPD()) {}

private:
    int gerarPV() {
        return rand() % (100 - 80 + 1) + 80;
    }

    int gerarPA() {
        return rand() % (25 - 10 + 1) + 10;
    }

    int gerarPD() {
        return rand() % (25 - 20 + 1) + 20;
    }
};

class Druida : public Personagem { // ganha escudo
//ataque elemental - ataque com mais chance de sangramento
public:
    Druida()
        : Personagem(gerarNomeAleatorio(), "Druida", gerarPV(), gerarPA(), gerarPD()) {}

private:
    int gerarPV() {
        return rand() % (100 - 90 + 1) + 90;
    }

    int gerarPA() {
        return rand() % (30 - 20 + 1) + 20;
    }

    int gerarPD() {
        return rand() % (20 - 15 + 1) + 15;
    }
};

class Clerigo : public Personagem { // se cura
//Ascensão celestial - cura em si
public:
    Clerigo()
        : Personagem(gerarNomeAleatorio(), "Clerigo", gerarPV(), gerarPA(), gerarPD()) {}

private:
    int gerarPV() {
        return rand() % (90 - 75 + 1) + 75;
    }

    int gerarPA() {
        return rand() % (20 - 15 + 1) + 15;
    }

    int gerarPD() {
        return rand() % (23 - 15 + 1) + 15;
    }
};

class Ladino : public Personagem { // causa dano alto e tem chance de causar sangramento
 //Sombra mortal - dano massivo e sangramento
public:
    Ladino()
        : Personagem(gerarNomeAleatorio(), "Ladino", gerarPV(), gerarPA(), gerarPD()) {}

private:
    int gerarPV() {
        return rand() % (90 - 70 + 1) + 70;
    }

    int gerarPA() {
        return rand() % (35 - 25 + 1) + 25;
    }

    int gerarPD() {
        return rand() % (25 - 15 + 1) + 15;
    }
};

int main() {
    srand(static_cast<unsigned>(time(nullptr)));

    string nome, classe;
    JogoRPG jogoRPG;
    cout <<"Digite o nome: " << endl;
    cin >> nome;
    cout <<"Digite a classe: " << endl;
    cin >> classe;

    if(classe=="bruxo" || classe=="Bruxo"){
        Bruxo nome; 
    }else if(classe=="clerigo" || classe=="Clerigo"){
        Clerigo nome; 
    }else if(classe=="ladino" || classe=="Ladino"){
        Ladino nome; 
    }else if(classe=="guerreiro" || classe=="Guerreiro"){
        Guerreiro nome; 
    }else if(classe=="mago" || classe=="Mago"){
        Mago nome; 
    }else if(classe=="druida" || classe=="Druida"){
        Druida nome; 
    };


    // Adicionando os personagens ao vetor
    vector<Personagem*> participantes = {
        &bruxo1, &bruxo2, &bruxo3,
        &clerigo1, &clerigo2,
        &ladino1, &ladino2, &ladino3,
        &guerreiro1, &guerreiro2, &guerreiro3,
        &mago1, &mago2, &mago3,
        &druida1, &druida2
    };

    // Fase de combates
    int fase = 1;

    while (participantes.size() > 1) {
        cout << "\n------ Fase " << fase << " ------" << endl;
        for (Personagem* participante : participantes) {
        participante->resetarAtributos();
        }
        vector<Personagem*> vencedores;

    for (int i = 0; i < participantes.size(); i += 2) {
        cout << "\nCombate: " << participantes[i]->getNome() << " vs " << participantes[i + 1]->getNome() << endl;
        jogoRPG.iniciarCombate(participantes[i], participantes[i + 1]);

        participantes[i]->resetarAtributos();
        participantes[i + 1]->resetarAtributos();

        if (participantes[i]->getPV() > 0) {
            vencedores.push_back(participantes[i]);
        } else {
            vencedores.push_back(participantes[i + 1]);
        }
    }

    // Atualizando participantes para a próxima fase  
    participantes.clear();
    for (Personagem* vencedor : vencedores) {
        vencedor->resetarAtributos();
        participantes.push_back(vencedor);
    }
        fase++;
    }

    // Exibindo o vencedor final
    cout << "\n------ VENCEDOR FINAL ------\n";
    cout << "O grande vencedor é: " << participantes[0]->getNome() << "!\n";

    return 0;
}