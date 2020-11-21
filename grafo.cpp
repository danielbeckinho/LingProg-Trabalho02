#include "grafo.h"

//bool operator==(std::string &palavra, Vertice &vertice) { }

bool Vertice::operator==(std::string &palavra) {
    return (this->key == palavra);
}

Vertice::Vertice(std::string &palavra) {
    this->key = palavra;
    this->pesoV = 1;
}






Aresta::Aresta(Vertice *verticeIn, Vertice *verticeFi) {
    this->verticeInicial = verticeIn;
    this->verticeFinal = verticeFi;
    this->pesoA = 1;
}









Vertice *Grafo::findVertice(std::string &palavra) {
    //se encontrar vertice correspondente aa palavra retorna imediatamente, se nao NULL
    if (grafoVertices.size() == 0) {return NULL;}

    for (auto vertice : grafoVertices) {
        if (*vertice == palavra) {return vertice;}
    }

    return NULL; 
}

Aresta *Grafo::findAresta(Vertice *verticeIn, Vertice *verticeFi) {
    if (grafoArestas.size() == 0) {return NULL;}

    for (auto aresta : grafoArestas) {
        if ((aresta->verticeInicial == verticeIn) && (aresta->verticeFinal == verticeFi)) {return aresta;}
    }

    return NULL;
}




std::vector<std::string> separaPalavras(std::string &frase){
    char delimiter = ' ';
    size_t pos_f{0};
    std::string buffer = frase;

    std::vector<std::string> palavras;

    while (pos_f != std::string::npos){
        pos_f = buffer.find_first_of(delimiter, 0);

        std::string palavra = buffer.substr(0,pos_f);
        buffer.erase(0, pos_f + 1);

        palavras.push_back(palavra);
    }

    return palavras;
}

void Grafo::gerarGrafo(std::vector<std::string> frases) {
    //percorrer frases uma a uma
        //checar palavra por palavra e ver se vertice E e criar ou inc pesoV
        //checar vertices da frase 2 a 2 na ordem e ver se aresta E e criar ou inc pesoA
    
    for (auto frase : frases) {
        std::vector<std::string> palavras = separaPalavras(frase);

        for (auto palavra :palavras){ //criar vertices caso necessario, caso nao incrementar pesoV

            if (findVertice(palavra) == NULL) {grafoVertices.push_back(new Vertice(palavra));}
            else findVertice(palavra)->pesoV++;

        }

        Vertice *verticePassado;
        Vertice *verticeAtual;
        for (size_t i{0}; i < palavras.size(); i++) { //criar arestas caso necessario, caso nao incrementar pesoA
            std::string palavra = palavras[i];

            if (i == 0) { verticeAtual = findVertice(palavra);}

            else {
                verticePassado = verticeAtual;
                verticeAtual = findVertice(palavra);

                if (findAresta(verticePassado, verticeAtual) == NULL) {grafoArestas.push_back(new Aresta(verticePassado, verticeAtual));}
                else findAresta(verticePassado, verticeAtual)->pesoA++;
                
            }


        }
    }
}




/*

        char delimiter = ' ';
        //size_t pos_i{0};
        size_t pos_f{0};
        std::string buffer = frase;

        //pos_i = buffer.find_first_not_of(delimiter);
        pos_f = buffer.find_first_of(delimiter, 0 //pos_i);

        std::string palavra = buffer.substr(0,pos_f);
        buffer.erase(0, pos_f + 1);

*/ 