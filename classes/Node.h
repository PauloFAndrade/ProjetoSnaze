#ifndef _NODE_H_
#define _NODE_H_

class Node{
    public:
        int walkable;
        int listaAberta;
        int listaFechada;
        int g,h,f;
        int parenteLinha;
        int parenteColuna; 
};

#endif