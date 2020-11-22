#include "grafo.h"

#include <algorithm>

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


void Grafo::criarVertice_ou_IncrementarPeso(std::string &palavra) {
    if (findVertice(palavra) == NULL) {grafoVertices.push_back(new Vertice(palavra));}
    else findVertice(palavra)->pesoV++;
}

void Grafo::instanciarVertices(std::vector<std::string> &palavras) {
    for (auto palavra :palavras){ //criar vertices caso necessario, caso nao incrementar pesoV
        criarVertice_ou_IncrementarPeso(palavra);
    }    
}


void Grafo::criarAresta_ou_IncrementarPeso(Vertice *verticeInicio, Vertice *verticeFim) {
    if (findAresta(verticeInicio, verticeFim) == NULL) {grafoArestas.push_back(new Aresta(verticeInicio, verticeFim));}
    else findAresta(verticeInicio, verticeFim)->pesoA++;   
}

void Grafo::instanciarArestas(std::vector<std::string> &palavras) {
    //
    Vertice *verticePassado;
    Vertice *verticeAtual;
    for (size_t i{0}; i < palavras.size(); i++) { //criar arestas caso necessario, caso nao incrementar pesoA
        std::string palavra = palavras[i];

        if (i == 0) { verticeAtual = findVertice(palavra);}

        else {
            verticePassado = verticeAtual;
            verticeAtual = findVertice(palavra);

            criarAresta_ou_IncrementarPeso(verticePassado, verticeAtual);
        }

    }
}

void Grafo::criarSA_ou_IncrementarPeso(std::vector<Vertice *> &verticesCandidatos) {
    SuperAresta *saPtr = findSuperAresta(verticesCandidatos);

    if (saPtr == NULL) { //verifica se SA jah existe, se NULL nao existe entao pode criar
        saPtr = new SuperAresta(verticesCandidatos); //cria nova SA e adiciona ao grafo
        grafoSuperArestas.push_back(saPtr);
    }

    else {saPtr->pesoSA++;} //se SA existe incrementa pesoSA
    
}

void Grafo::instanciarSuperArestas_filhas(SuperAresta &saMae) {
    std::vector<Vertice *> verticesSA_Mae = saMae.verticesSuperAresta;

    //agora vamos criar ou inc peso de novas SA a partir dos vertices da mae
    //vamos usar vetores de tamanho numVerticesMae-1 a 2 (no caso limite todas as aresta sao SA)
    //respeitando sempre a ordem que as palavras aparecem na frase, que estao implicitas na ordem de formacao do vetorVerticesMae
    size_t sizeSA_M = verticesSA_Mae.size();
    size_t sizeSA_f = sizeSA_M - 1;
    size_t sizeSA_min = 2; //tamanho minimo de SA

    std::vector<Vertice *> verticesCandSA_f;

    for (sizeSA_f; sizeSA_f >= sizeSA_min; sizeSA_f--) { //determina tamanho dos vetores de vertices candidatos a serem gerados e testados
        
        for (size_t pos_fi{sizeSA_f}; pos_fi <= sizeSA_M; pos_fi++) { //gera vetores de vertices cand
            size_t pos_in = pos_fi - sizeSA_f; //pos in do vetor de vertices candidatos da filha; pos_fi - pos_in = sizeSA_f, ie, o tamanho do vetor de cand da filha  

            //std::copy(verticesSA_Mae.begin() + pos_in, verticesSA_Mae.begin() + pos_fi, verticesCandSA_f.begin()); //copia do vetor de vertices da mae um subtrecho com tamanho menor que o da mae, repete isso pra todas as possibilidade que respeitem a ordem dos vertices_Mae

            for (size_t k{0}; k < sizeSA_f; k++) {
                verticesCandSA_f.push_back(verticesSA_Mae[k+pos_in]);
            }

            criarSA_ou_IncrementarPeso(verticesCandSA_f); //cria ou incrementa SA_filha a partir do subconjunto de vertices da mae

            verticesCandSA_f.clear();
        }
    }


}

void Grafo::instanciarSuperArestas(std::vector<std::string> &palavras) {
    std::vector<Vertice *> verticesCandSA;
    for (size_t i{0}; i < palavras.size(); i++) {
            
        Vertice *verticePtr = findVertice(palavras[i]);

        if (verticesCandSA.size() == 0) {verticesCandSA.push_back(verticePtr);}

        else if (isInVectorVertice(verticePtr, verticesCandSA)) { //se vertice isInVectorVertice, eh vertice repetido entao para e cria SA mae. caso cont adiciona ao vector e continua
                
            criarSA_ou_IncrementarPeso(verticesCandSA);
            SuperAresta saMae = *findSuperAresta(verticesCandSA);

            instanciarSuperArestas_filhas(saMae);

            verticesCandSA.clear(); //limpa o vector pra possibilitar criacao de nova SA ainda nessa frase
        }

        else {
            verticesCandSA.push_back(verticePtr);
        }

    }

    criarSA_ou_IncrementarPeso(verticesCandSA); //acabaram as palvras (e potenciais vertices) da frase, tenta criar SA com palavras restantes
    SuperAresta saMae = *findSuperAresta(verticesCandSA);

    instanciarSuperArestas_filhas(saMae);
}


void Grafo::gerarGrafo(std::vector<std::string> frases) {
    //percorrer frases uma a uma
        //checar palavra por palavra e ver se vertice E e criar ou inc pesoV
        //checar vertices da frase 2 a 2 na ordem e ver se aresta E e criar ou inc pesoA
    
    for (auto frase : frases) {
        std::vector<std::string> palavras = separaPalavras(frase);

        instanciarVertices(palavras); //checa se vertice ja existe, se sim incrementa peso, se nao cria

        instanciarArestas(palavras); //checa se aresta ja existe, se sim incrementa peso, se nao cria

        instanciarSuperArestas(palavras); //checa se SuperAresta existe, se sim incrementa peso dela e filhas, se nao cria SA e a partir dela repete o processo pra criar SA-filhas (SA menores, contidas na SA mae)

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