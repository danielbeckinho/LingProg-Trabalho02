#include "processadorTexto.h"

#include <algorithm>
#include <fstream>

static const std::string fileName{"texto.txt"};


size_t minVal(size_t a, size_t b, size_t c) {
    size_t min = std::min(std::min(a,b),std::min(b,c));
    return min;
}

std::string cleanString(std::string string) {
    std::vector<char> delimiters{'"', '\'', '/', '(', ')', '\\', '\n'};
    for (auto delimiter :delimiters) {
        size_t pos{0};
        pos = string.find(delimiter);

        while (pos != std::string::npos) {
            std::string stringL;
            std::string stringR;

            stringL = string.substr(0,pos);
            stringR = string.substr(pos+1);
            string = stringL + stringR;

            pos = string.find(delimiter);
        }

    }
    return string;
}

std::string sToLower(std::string s){
    transform(s.begin(), s.end(), s.begin(), ::tolower);
    return s; 
    
}

std::vector<std::string> removeLeadWhitespace(std::vector<std::string> stringV) {
    for (size_t i{0}; i < stringV.size(); i++) {
        size_t start = stringV[i].find_first_not_of(' ');
        stringV[i] = stringV[i].substr(start);
    }
    return stringV;
}


std::vector<std::string> processText() {
    std::vector<std::string> frases;
    std::string frase;

    std::ifstream in_file;
    in_file.open(fileName);

    if (in_file.is_open()){
        std::string buffer;

        while (getline(in_file, buffer, '.')) { 
            buffer = cleanString(buffer);
            
            std::size_t posNow, posOld = 0;
            while ((posNow = buffer.find_first_of(",;:", posOld)) != std::string::npos){

                if (posNow > posOld) {
                    frase = buffer.substr(posOld, posNow-posOld);
                    frase = sToLower(frase);
                    frases.push_back(frase);
                    posOld = posNow + 1;
                }
            }

            if (posOld < buffer.length()) {
                frase = buffer.substr(posOld, std::string::npos);
                frase = sToLower(frase);
                frases.push_back(frase);
            }       
 
        }

        in_file.close();
    }
    frases = removeLeadWhitespace(frases);
    return frases;
}

