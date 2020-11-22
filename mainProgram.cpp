#include "processadorTexto.h"
#include "grafo.h"

#include <iostream>

int main() {
    std::vector<std::string> frases = processText();

    Grafo grafo;

    grafo.gerarGrafo(frases);

    for (auto frase :frases) {
        std::cout << frase <<std::endl;
    }
}