//
// Created by arturocv on 19/09/17.
//

#ifndef RMLIB_NODE_H
#define RMLIB_NODE_H


template <class T>
class Node {
private:
    T data;
    Node<T> *next;

public:
    Node(T data);

    void setData(T data);

    T getData();

    void setNext(Node *next);

    Node* getNext();
};



#endif //RMLIB_NODE_H
