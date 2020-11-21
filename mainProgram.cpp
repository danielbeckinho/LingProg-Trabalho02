#include "processadorTexto.h"

#include <iostream>

int main() {
    std::vector<std::string> frases = funcName();

    for (auto frase :frases) {
        std::cout << frase;
    }
}