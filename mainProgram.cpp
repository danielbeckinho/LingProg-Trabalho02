#include "processadorTexto.h"

#include <iostream>

int main() {
    std::vector<std::string> frases = processText();

    for (auto frase :frases) {
        std::cout << frase <<std::endl;
    }
}