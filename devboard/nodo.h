#ifndef NODE_H
#define NODE_H


template<class T>
class Node
{

private:
    Node* prox;
    Node* ant;
    T* objeto;

public:
    Node();
    Node(T*);
    ~Node();

    void setProx(Node*);
    void setAnt(Node*);
    void setInfo(T);
    Node* getProx();
    Node* getAnt();
    T getInfo();
    //void exibir( );
};



#endif // NODE_H
