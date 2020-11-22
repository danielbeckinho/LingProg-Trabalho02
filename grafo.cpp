#include "grafo.h"

//bool operator==(std::string &palavra, Vertice &vertice) { }

bool Vertice::operator==(std::string &palavra) {
    return (this->key == palavra);
}

bool SuperAresta::operator==(std::vector<Vertice *> &verticesCandSA) { //verticesCandSA leia-se Vertices Candidatos a Super Aresta
    if (this->verticesSuperAresta.size() != verticesCandSA.size()) {return false;}

    else {
        for (size_t i{0}; i < this->verticesSuperAresta.size(); i++) {
            if (this->verticesSuperAresta[i] != verticesCandSA[i]) {return false;}
        }
        return true;
    }

}


Vertice::Vertice(std::string &palavra) {
    key = palavra;
    pesoV = 1;
}


Aresta::Aresta(Vertice *verticeIn, Vertice *verticeFi) {
    verticeInicial = verticeIn;
    verticeFinal = verticeFi;
    pesoA = 1;
}


SuperAresta::SuperAresta(std::vector<Vertice *> verticesSA) {
    verticesSuperAresta = verticesSA;
    pesoSA = 1;
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


SuperAresta *Grafo::findSuperAresta(std::vector<Vertice *> verticesFindSA) {
    if (grafoSuperArestas.size() == 0) {return NULL;}

    else {
        for (auto SuperA : grafoSuperArestas) {
            if (*SuperA == verticesFindSA) {return SuperA;}
        }
    }
    return NULL;
}


bool Grafo::isInVectorVertice(Vertice *verticePtr, std::vector<Vertice *> &verticesCandidatos) {
    //checa o vetor de vertices candidatos aa formar SuperAresta se palavra, ie, vertice ja esta no vetor
    for (auto vertice : verticesCandidatos) {
        if (vertice == verticePtr) {return true;}
    }

    return false;
}


std::vector<std::string> Grafo::separaPalavras(std::string &frase){
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

        //criar SuperArestas
        //cada frase pode originar pelo menos uma SA, que depois pode originar SAs filhas
        //ATENCAO em uma SA nao pode ter repeticao de vertice. 
        std::vector<Vertice *> verticesCandSA;
        for (size_t i{0}; i < palavras.size(); i++) {
            
            Vertice *verticePtr = findVertice(palavras[i]);

            if (verticesCandSA.size() == 0) {verticesCandSA.push_back(verticePtr);}

            else if (isInVectorVertice(verticePtr, verticesCandSA)) { //se nenhum vertice repetido adiciona vertice ao vetor, se repetido cria SA mae
                
                if (findSuperAresta(verticesCandSA) == NULL) { //verifica se SA jah existe, se NULL nao existe entao pode criar
                    SuperAresta *sa = new SuperAresta(verticesCandSA); //cria nova SA e adiciona ao grafo
                    grafoSuperArestas.push_back(sa);
                }
                else {findSuperAresta(verticesCandSA)->pesoSA++;} //se SA existe incrementa pesoSA
                
                verticesCandSA.clear(); //limpa o vector pra possibilitar criacao de nova SA
            }

            else {
                verticesCandSA.push_back(verticePtr);
            }

        }

        if (findSuperAresta(verticesCandSA) == NULL) {grafoSuperArestas.push_back(new SuperAresta(verticesCandSA));} //acabaram as palvras da frase, tenta criar SA com palavras restantes
        else findSuperAresta(verticesCandSA)->pesoSA++;


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