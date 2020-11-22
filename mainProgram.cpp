#include "processadorTexto.h"
#include "grafo.h"
#include "estatisticas.h"

#include <iostream>


int menu() {
    int sel;

    std::cout << "        Menu" << std::endl;

    std::cout << "(1) Palavra mais frequente no paragrafo. \n"
              << "(2) Sequencia de palavras mais frequente no paragrafo. \n"
              << "(0) Sair. \n" << std::endl;

    std::cout << "Opcao: "; std::cin >> sel;

    return sel;
}

int main() {
    std::vector<std::string> frases = processText();

    Grafo grafo;

    grafo.gerarGrafo(frases);

    Stats stats = Stats(grafo);

    bool run = true;

    while (run == true) {
        int sel = menu();
        
        if (sel == 0) {run = false;}

        else if (sel == 1) {stats.getPalavrasMaisFreq();}

        else if (sel == 2) {stats.getSeqPalavrasMaisFreq();}
    } 
}