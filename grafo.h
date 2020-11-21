#ifndef GRAFO_H
#define GRAFO_H

#include <string>
#include <vector>

class Vertice {
    
    friend class Aresta;
    friend class Grafo;

    //friend operator==(std::string &, Vertice &);

    public:
        Vertice(std::string &);

        bool operator==(std::string &);


    private:
        std::string key;
        int pesoV;




};


class Aresta {
    
    friend class Grafo;

    public:
        Aresta(Vertice*, Vertice*); //criar c/ verticeIni e verticeFinal
       
        




    private:
        Vertice *verticeInicial;
        Vertice *verticeFinal;
        int pesoA;
};

class Grafo {
    public:
        void gerarGrafo(std::vector<std::string>);
    
        Vertice *findVertice(std::string &);
        Aresta *findAresta(Vertice *, Vertice*);

        std::vector<std::string> separaPalavras(std::string &);

    private:
        std::vector<Vertice *> grafoVertices;
        std::vector<Aresta *> grafoArestas;



};

class SuperAresta {
    public:



    private:
        std::vector<Vertice *> verticesSuperA;  


};











#endif