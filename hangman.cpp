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
    entrada.open("data.txt");

    if (entrada.is_open()) {
        entrada >> maiorStreak;
        entrada >> streak;

        entrada.close();
    }
}

void salvarDados(int &maiorStreak, int &streak) {
    ofstream saida;
    saida.open("data.txt");

    saida << maiorStreak << endl;
    saida << streak << endl;

    saida.close();
}

string sortearPalavra(int idioma) {
    int indice = rand() % 344;
    string palavra;
    ifstream dicionario;

    if (idioma == 1)
        dicionario.open("pt.txt");
    if (idioma == 2)
        dicionario.open("en.txt");

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

void menuDificuldade(float &dicas, int &tentativas) {
    int opc = 0;

    while (opc < 1 || opc > 3) {
        system(CLEAR);
        cout << "\n\t\t HANGMAN\n\n";
        cout << "  [1] - Facil." << endl;
        cout << "  [2] - Medio." << endl;
        cout << "  [3] - Dificil." << endl;
        cout << "\n         Escolha a dificuldade: ";
        cin >> opc;
        cin.ignore();
        cout << endl;

        switch (opc) {
        case 1:
            dicas = 2;
            tentativas = 9;
            break;
        case 2:
            dicas = 1;
            tentativas = 8;
            break;
        case 3:
            dicas = 0;
            tentativas = 7;
            break;
        default:
            cout << "\t     Opcao invalida.";
            getchar();
            cin.clear();
            cout << endl;
            break;
        }
    }
}

int menuInicial() {
    int opc = 0;

    while (opc < 1 || opc > 2) {
        system(CLEAR);
        cout << "\n\t\t HANGMAN\n\n";
        cout << "  [1] - Portugues(BR)." << endl;
        cout << "  [2] - Ingles." << endl;
        cout << "\n           Escolha o idioma: ";
        cin >> opc;
        cin.ignore();
        cout << endl;

        if (opc <= 2 && opc >= 1) break;
        
        cout << "\t     Opcao invalida.";
        getchar();
        cin.clear();
        cout << endl;
    }

    return opc;
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
        cout << "    Para dica digite \"?\" [" << (int)dicas << " no total]\n\n";
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
        cin.ignore();
        letra = tolower(letra);

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
        dicas += 0.4;
        streak++;

        if (streak > maiorStreak) 
            maiorStreak = streak;
    } else {
        cout << "\n\t       VOCE PERDEU!";
        dicas += 0.25;
        streak = 0;
    }
    
    hangman(tentativas);
    char opc;
    cout << "  A palavra era: " << palavra << "\n\n";
    cout << "  Deseja continuar? (S/N) ";
    cin >> opc;
    opc = toupper(opc);

    return opc;
}

int main() {
    srand(time(0));
    int streak = 0, maiorStreak = 0, tentativas = 0;
    float dicas = 1;

    int idioma = menuInicial();
    menuDificuldade(dicas, tentativas);
    receberDados(maiorStreak, streak);

    while (novaPalavra(maiorStreak, streak, tentativas, dicas, idioma) != 'N');
    
    salvarDados(maiorStreak, streak);
    return 0;
}