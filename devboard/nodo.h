template<class T>
class Node
{
    T* data;
    Node* next;
public:
    Node() {};
    void setData(T* aData) { data = aData; };
    void setNext(Node* aNext) { next = aNext; };
    T* getData() { return data; };
    Node* getNext() { return next; };
};
