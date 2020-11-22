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
        SuperAresta *findSuperAresta(std::vector<Vertice *>);

        bool isInVectorVertice(Vertice *, std::vector<Vertice *> &);

        std::vector<std::string> separaPalavras(std::string &);

        void instanciarVertices(std::vector<std::string> &);
        void instanciarArestas(std::vector<std::string> &);
        void instanciarSuperArestas(std::vector<std::string> &);

        

    private:
        std::vector<Vertice *> grafoVertices;
        std::vector<Aresta *> grafoArestas;
        std::vector<SuperAresta *> grafoSuperArestas;



};

class SuperAresta {
    
    friend class Grafo;

    public:
        SuperAresta(std::vector<Vertice *>);

        bool operator==(std::vector<Vertice *> &); //vai ser usado pra compara uma SA existente com um vector de Vertice* candidato a ser nova SA

    private:
        std::vector<Vertice *> verticesSuperAresta;
        int pesoSA;  


};











#endif