#include "processadorTexto.h"

#include <fstream>

static const std::string fileName{"texto.txt"};



std::string cleanString(std::string string) {
    std::vector<char> delimiters{'"', '\'', '/', '(', ')', '\\'};
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


std::vector<std::string> funcName() {
    std::vector<std::string> frases;
    
    std::ifstream in_file;
    in_file.open(fileName);

    if (in_file.is_open()){
        std::string buffer;

        while (getline(in_file, buffer, '.')) { 
            buffer = cleanString(buffer);
            
            size_t pos_comma{buffer.find(',')};
            size_t pos_semic{buffer.find(';')};
            size_t pos_colon{buffer.find(':')};

            std::string frase;

            while ((pos_comma != std::string::npos) || (pos_semic != std::string::npos) || (pos_colon != std::string::npos)) {
                size_t min_pos = std::min(pos_comma , pos_semic , pos_colon);

                frase = buffer.substr(0, min_pos);
                buffer = buffer.substr(min_pos+1);

                frases.push_back(frase);

                size_t pos_comma{buffer.find(",")};
                size_t pos_semic{buffer.find(";")};
                size_t pos_colon{buffer.find(":")};
            }
 
        }

        in_file.close();
    }
    return frases;
}


