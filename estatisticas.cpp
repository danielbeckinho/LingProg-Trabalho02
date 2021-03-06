#include "estatisticas.h"

#include <iostream>

std::vector<Vertice *> Stats::instanciarPalavraMaisFreq(Grafo &grafo) { //usada para inicializar o vetor que contem o ou os vertices (em caso de empate) de maior numero de repeticoes, ie peso, no paragrafo  
    std::vector<Vertice *> palavrasMaisFreq;
    int pesoMax{0};

    for (auto vertice : grafo.getGrafoVertices()) { //comparacao vertice a vertice atualizando pesoMax conforme necessario
        if (vertice->getPesoV() > pesoMax) {
            pesoMax = vertice->getPesoV();
            palavrasMaisFreq.clear(); //quando se atualiza o vetor que contem o(s) vertices de maior peso eh limpo
            palavrasMaisFreq.push_back(vertice);
        }

        else if (vertice->getPesoV() == pesoMax) { //em caso de empate usamos este vetor pra armazenar os verices
            palavrasMaisFreq.push_back(vertice);
        }
    }
    return palavrasMaisFreq;
}

std::vector<std::vector<SuperAresta *>> Stats::instanciarSeqPalavrasMaisFreq(Grafo &grafo) {
    size_t indexSize{0};
    for (auto sa : grafo.getGrafoSuperArestas()) { if (sa->getSizeSA() > indexSize) {indexSize = sa->getSizeSA();}}
    indexSize+=1;

    std::vector<std::vector<SuperAresta *>> seqPalavrasPorTamanho(indexSize, std::vector<SuperAresta *> ()); //nesse vetor de vetor o indice principal eh o tamanho das SA que o compoe depois vou iterar sobre ele pra obter os maiores pesos
    std::vector<std::vector<SuperAresta *>> seqPalavrasPorTamanho_MaiorFreq(indexSize, std::vector<SuperAresta *> ()); //indice prin eh o tamanho da SA, mas agora no vetor de SA soh tem as que tem o peso maior, ie maior freq

    std::vector<SuperAresta *> dummyVec; //vetor dummy pra posicao zero do seqPalavrasPorTamanho

    seqPalavrasPorTamanho.push_back(dummyVec);

    for (auto sa : grafo.getGrafoSuperArestas()) { //processo analago ao feito em instanciarPalavrasMaisFreq (linha 5)
        size_t indice = sa->getSizeSA();

        if (seqPalavrasPorTamanho[indice].size() == 0) {
            std::vector<SuperAresta *> vecSA{sa};
            seqPalavrasPorTamanho[indice] = vecSA;
        }

        else {seqPalavrasPorTamanho[indice].push_back(sa);}

    }

    for (size_t i{1}; i < seqPalavrasPorTamanho.size(); i++) {
        int pesoMax{0};

        for (auto sa :seqPalavrasPorTamanho[i]) {
            if (sa->getPesoSA() > pesoMax) {
                pesoMax = sa->getPesoSA();

                seqPalavrasPorTamanho_MaiorFreq[i].clear();

                std::vector<SuperAresta *> vecSA{sa};
                seqPalavrasPorTamanho_MaiorFreq[i] = vecSA;
            }

            else if (sa->getPesoSA() == pesoMax) {seqPalavrasPorTamanho_MaiorFreq[i].push_back(sa);}
        } 
    
    }

    return seqPalavrasPorTamanho_MaiorFreq;
}

void Stats::getPalavrasMaisFreq() const { //esta funcao eh soh um exibidor dos resultados previamente calculados
    if (verticesMaisFreq.size() == 1) {
        std::cout << "A palavra mais frequente eh: " << "\"" << verticesMaisFreq[0]->getKey() << "\" "
            << "com " << verticesMaisFreq[0]->getPesoV() << " repeticoes." << std::endl;
    }

    else {
        std::cout << "As palavras mais frequentes com " << verticesMaisFreq[0]->getPesoV() << " repeticoes, sao: \n" << std::endl;

        for (auto vertice : verticesMaisFreq) {
            std::cout << vertice->getKey() << std::endl;
        }

        std::cout << std::endl;
    }
}

void Stats::getSeqPalavrasMaisFreq() const { //esta funcao eh soh um exibidor dos resultados previamente calculados
    bool validInput = false;
    size_t maxInput = superArestasMaisFreq.size(); //o indice princ desse vetor eh o tamanho das SA que estao nos subvetores
    size_t sizeSeq;

    while (validInput == false) {
        std::cout << "Escolha um tamanho para a sequencia de palavras. O tamanho deve ser 2 < tamanho < " << maxInput << " e inteiro. \n";
        std::cout << "Tamanho: ";

        std::cin >> sizeSeq;

        if ((sizeSeq > 0) && (sizeSeq < maxInput)) {validInput = true;}

        std::cout << "\n" << std::endl;

    }

    if (superArestasMaisFreq[sizeSeq].size() == 1) {
        std::cout << "A sequencia mais frequente de palavras, com " << superArestasMaisFreq[sizeSeq][0]->getPesoSA() << " repeticoes eh: \n" << std::endl;

        for (auto sa : superArestasMaisFreq[sizeSeq]) {
            //std::vector<Vertice *> vecVertSA = sa->getVerticesSuperAresta();
            for (size_t i{0}; i < sa->getSizeSA(); i++) {

                std::cout << sa->getVerticesSuperAresta()[i]->getKey() << " "; 
            }
            std::cout << "\n" << std::endl;
        }
    }

    else if (superArestasMaisFreq[sizeSeq].size() != 0) {
        std::cout << "As sequencias mais frequentes de palavras, com " << superArestasMaisFreq[sizeSeq][0]->getPesoSA() << " repeticoes sao: \n" << std::endl;

        for (auto sa : superArestasMaisFreq[sizeSeq]) {
            //std::vector<Vertice *> vecVertSA = sa->getVerticesSuperAresta();
            for (size_t i{0}; i < sa->getSizeSA(); i++) {

                std::cout << sa->getVerticesSuperAresta()[i]->getKey() << " "; 
            }
            std::cout << "\n" << std::endl;

        }
    }

    else {std::cout << "Nenhuma sequencia para este tamanho." << std::endl;}
}



