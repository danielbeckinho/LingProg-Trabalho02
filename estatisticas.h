#ifndef ESTATISTICAS_H
#define ESTATISTICAS_H

#include "grafo.h"

#include <vector>

class Stats {
    public:
        Stats(Grafo &grafo) {
            verticesMaisFreq = instanciarPalavraMaisFreq(grafo);
            superArestasMaisFreq = instanciarSeqPalavrasMaisFreq(grafo);
        }

        std::vector<Vertice *> instanciarPalavraMaisFreq(Grafo &);

        std::vector<std::vector<SuperAresta *>> instanciarSeqPalavrasMaisFreq(Grafo &grafo);

        void getPalavrasMaisFreq() const;

        void getSeqPalavrasMaisFreq() const;

    private:
        std::vector<Vertice *> verticesMaisFreq;
        std::vector<std::vector<SuperAresta *>> superArestasMaisFreq;
        
};




















#endif