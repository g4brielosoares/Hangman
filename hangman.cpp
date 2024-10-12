#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <set>

#ifdef _WIN32
    #define CLEAR "cls"
#else
    #define CLEAR "clear"
#endif

using namespace std;

void receberDados(int &maiorStreak, int &streak) {
    ifstream entrada;

    entrada.open("../dados/dados.txt", ios::in);

    if (entrada.is_open()) {
        entrada >> maiorStreak;
        entrada >> streak;

        entrada.close();
    }
}

void salvarDados(int &maiorStreak, int &streak) {
    ofstream saida;

    saida.open("../dados/dados.txt", ios::in);

    saida << maiorStreak << endl;
    saida << streak << endl;

    saida.close();
}

string sortearPalavra(int idioma) {
    int tam;
    if (idioma == 1) tam = 486;
    if (idioma == 2) tam = 409;

    int indice = rand() % tam;
    string palavra;
    ifstream dicionario;

    if (idioma == 1) 
        dicionario.open("../lang/pt.txt", ios::in);
    if (idioma == 2)
        dicionario.open("../lang/en.txt", ios::in);
    

    if (dicionario.is_open()) {
        for (int i = 0; i <= indice; i++)
            getline(dicionario, palavra);
    }

    dicionario.close();

    return palavra;
}

char gerarDica(string palavra, vector<char> &espacosEmBranco) {
    vector<int> naoReveladas;

    for (int i = 0; i < (int)palavra.length(); i++) 
        if (espacosEmBranco[i] == '_') naoReveladas.push_back(i);
    
    if (naoReveladas.empty()) return '\0';

    int randIndice = rand() % naoReveladas.size();
    return palavra[naoReveladas[randIndice]];
}

int revelarLetras(string palavra, vector<char> &espacosEmBranco, char letra) {
    int quant = 0;

    for (int i = 0; i < (int)palavra.length(); i++) {
        if (palavra[i] == letra) {
            espacosEmBranco[i] = letra;
            quant++;
        }
    }

    return quant;
}

bool buscarLetraDigitada(set<char> &letrasDigitadas, char letra) {
    if (letrasDigitadas.count(letra) > 0) return true;
    letrasDigitadas.insert(letra);
    return false;
}

void hangman(int tentativas) {
    cout << "\n_________________________________________\n";

    if (tentativas >= 9) {
        cout << endl;
        cout << endl;
        cout << endl;
        cout << endl;
        cout << endl;
        cout << endl;
    }
    if (tentativas == 8) {
        cout << "\t\t ," << endl;
        cout << "\t\t |" << endl;
        cout << "\t\t |" << endl;
        cout << "\t\t |" << endl;
        cout << "\t\t |" << endl;
        cout << "\t\t |" << endl;
    }
    if (tentativas == 7) {
        cout << "\t\t ," << "____," << endl;
        cout << "\t\t |" << endl;
        cout << "\t\t |" << endl;
        cout << "\t\t |" << endl;
        cout << "\t\t |" << endl;
        cout << "\t\t |" << endl;
    }
    if (tentativas == 6) {
        cout << "\t\t ," << "____," << endl;
        cout << "\t\t |" << "    |" << endl;
        cout << "\t\t |" << endl;
        cout << "\t\t |" << endl;
        cout << "\t\t |" << endl;
        cout << "\t\t |" << endl;
    }
    if (tentativas == 5) {
        cout << "\t\t ," << "____," << endl;
        cout << "\t\t |" << "    |" << endl;
        cout << "\t\t |" << "    @" << endl;
        cout << "\t\t |" << endl;
        cout << "\t\t |" << endl;
        cout << "\t\t |" << endl;
    }
    if (tentativas == 4) {
        cout << "\t\t ," << "____," << endl;
        cout << "\t\t |" << "    |" << endl;
        cout << "\t\t |" << "    @" << endl;
        cout << "\t\t |" << "    |" << endl;
        cout << "\t\t |" << endl;
        cout << "\t\t |" << endl;
    }
    if (tentativas == 3) {
        cout << "\t\t ," << "____," << endl;
        cout << "\t\t |" << "    |" << endl;
        cout << "\t\t |" << "    @" << endl;
        cout << "\t\t |" << "    |\\" << endl;
        cout << "\t\t |" << endl;
        cout << "\t\t |" << endl;
    } 
    if (tentativas == 2) {
        cout << "\t\t ," << "____," << endl;
        cout << "\t\t |" << "    |" << endl;
        cout << "\t\t |" << "    @" << endl;
        cout << "\t\t |" << "   /|\\" << endl;
        cout << "\t\t |" << endl;
        cout << "\t\t |" << endl;
    }
    if (tentativas == 1) {
        cout << "\t\t ," << "____," << endl;
        cout << "\t\t |" << "    |" << endl;
        cout << "\t\t |" << "    @" << endl;
        cout << "\t\t |" << "   /|\\" << endl;
        cout << "\t\t |" << "    '\\" << endl;
        cout << "\t\t |" << endl;
    }
    if (tentativas == 0) {
        cout << "\t\t ," << "____," << endl;
        cout << "\t\t |" << "    |" << endl;
        cout << "\t\t |" << "    X" << endl;
        cout << "\t\t |" << "   /|\\" << endl;
        cout << "\t\t |" << "   /'\\" << endl;
        cout << "\t\t |" << endl;
    }

    cout << "_________________________________________\n\n";
}

bool menuDificuldade(float &dicas, int &tentativas) {
    int opc = 0;

    while (true) {
        system(CLEAR);
        cout << "\n\t\t HANGMAN\n";
        cout << "_________________________________________\n";
        cout << "\n\t       DIFICULDADE\n\n";
        cout << "  [1] - Facil." << endl;
        cout << "  [2] - Medio." << endl;
        cout << "  [3] - Dificil." << endl;
        cout << "\n  [0] - Voltar." << endl;
        cout << "\n           Escolha uma opcao: ";
        cin >> opc;
        cin.ignore(1000, '\n');
        cout << endl;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
        } else {
            switch (opc) {
                case 0:
                    return false;
                case 1:
                    dicas = 2;
                    tentativas = 9;
                    return true;
                case 2:
                    dicas = 1;
                    tentativas = 8;
                    return true;
                case 3:
                    dicas = 0;
                    tentativas = 7;
                    return true;
            }
        }
    }
}

void menuInicial(float &dicas, int &tentativas, int &idioma) {
    int opc = 0;
    
    do {
        while (true) {
            system(CLEAR);
            cout << "\n\t\t HANGMAN\n";
            cout << "_________________________________________\n";
            cout << "\n\t\t IDIOMAS\n\n";
            cout << "  [1] - Portugues(BR)." << endl;
            cout << "  [2] - Ingles." << endl;
            cout << "\n           Escolha uma opcao: ";
            cin >> opc;
            cin.ignore(1000, '\n');
            cout << endl;

            if (cin.fail()) {
                cin.clear();
                cin.ignore(1000, '\n');
            } else {
                if (opc == 1 || opc == 2) {
                    idioma = opc;
                    break;
                }
            }
        }
    } while (!menuDificuldade(dicas, tentativas));
}

char novaPalavra(int &maiorStreak, int &streak,int tentativas, float &dicas, int idioma) {
    int quantEncontradas = 0, quantIncorretas = 0;
    string palavra = sortearPalavra(idioma), listaIncorretas;
    vector<char> espacosEmBranco(palavra.length(), '_');
    set<char> letrasDigitadas;
    char letra;

    while (tentativas != 0 && quantEncontradas != (int)palavra.length()) {
        system(CLEAR);
      // Cabeçalho
        cout << "\n  Streak atual: " << streak << " | Maior registrado: " << maiorStreak;
      // hangman
        hangman(tentativas);
      // Dica
        cout << "      Para dica digite \"?\" [" << (int)dicas;
        ((int)dicas == 1) ? cout << " dica]\n\n" : cout << " dicas]\n\n" ;
      // Blankspaces
        cout << "  >  ";
        for (char espaco : espacosEmBranco) cout << espaco << " ";
        cout << endl;
      // Letras incorretas
        cout << "\n  Incorretas: ";
        for (char letra : listaIncorretas) 
            (letra == listaIncorretas[0]) ? cout << letra : cout << ", " << letra;
        (!listaIncorretas.empty()) ? cout << "." << endl : cout << endl;
      // Inserção
        cout << "\n  Digite uma letra: ";
        cin >> letra;
        cin.ignore(1000, '\n');
        letra = tolower(letra);
      // Condições
        if (letra == '?') {
            if (dicas >= 1) {
                dicas--;
                char dica = gerarDica(palavra, espacosEmBranco);

                if (dica != '\0')
                    quantEncontradas += revelarLetras(palavra, espacosEmBranco, dica);
            } else {
                cout << "\n\t  Dicas insuficientes.";
                getchar();
            }
        } else if (buscarLetraDigitada(letrasDigitadas, letra)) {
            cout << "\n\t Caractere ja inserido.";
            getchar();
            cout << endl;
        } else {
            int retorno = revelarLetras(palavra, espacosEmBranco, letra);

            if (retorno == 0) {
                tentativas--;
                quantIncorretas++;

                listaIncorretas += letra;
            } else {
                quantEncontradas += retorno;
            }
        }
    }   

    system(CLEAR);
    if (quantEncontradas == (int)palavra.length()) {
        cout << "\n\t       VOCE GANHOU!";
        if (dicas < 5) dicas += 0.42;
        streak++;

        if (streak > maiorStreak) 
            maiorStreak = streak;
    } else {
        cout << "\n\t       VOCE PERDEU!";
        if (dicas < 5) dicas += 0.23;
        streak = 0;
    }
    
    hangman(tentativas);
    char opc;
    cout << "  A palavra era: " << palavra << "\n\n";
    cout << "  Deseja continuar? (S/N) ";
    cin >> opc;
    cin.ignore(10000, '\n');
    opc = toupper(opc);

    return opc;
}

int main() {
    srand(time(0));
    int streak = 0, maiorStreak = 0, tentativas = 0, idioma;
    float dicas = 1;

    menuInicial(dicas, tentativas, idioma);
    receberDados(maiorStreak, streak);

    while (novaPalavra(maiorStreak, streak, tentativas, dicas, idioma) != 'N');
    
    salvarDados(maiorStreak, streak);

    return 0;
}