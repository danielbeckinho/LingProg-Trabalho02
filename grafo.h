#ifndef GRAFO_H
#define GRAFO_H

#include <string>
#include <vector>

class Vertice {
    
    friend class Aresta;
    friend class Grafo;

    public:
        Vertice(std::string);

        bool operator==(Vertice *);


    private:
        std::string key;
        int pesoV;




};


class Aresta {
    
    friend class Grafo;

    public:
        Aresta(Vertice*, Vertice*); //criar c/ verticeIni e verticeFinal
       
        bool operator==(Aresta *);




    private:
        Vertice *verticeInicio;
        Vertice *verticeFinal;
        int pesoA;
};

class Grafo {
    public:




    private:
        std::vector<Vertice *> vertices;
        std::vector<Aresta *> arestas;



};

class SuperAresta {
    public:



    private:
        std::vector<Vertice *> verticesSuperA;


};











#endif