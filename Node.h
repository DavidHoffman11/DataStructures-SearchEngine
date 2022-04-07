#ifndef NODE_H
#define NODE_H
#include <iostream>
#include <string>

using namespace std;

template <typename T>
class Node {
public:
    template <class U> friend class AVL;
    template <class V> friend class Splay;
    template <class W> friend class RedBlack;

    T element;
    T indexNum;
    string color;
    Node<T> * left;
    Node<T> * right;
    Node<T>* parent;
    int height;

    Node();
    //Node(const T& theElement, Node<T>* lt, Node<T>* rt, int h = 0) : element(theElement), left(lt), right(rt), height(h), parent(NULL) {}
    Node(const T& theElement, Node<T>* lt, Node<T>* rt, string c = "BLACK") : element(theElement), left(lt), right(rt), color(c) {}
    //Node(const T& theElement, int index, Node<T>* lt, Node<T>* rt, int h = 0) : element(theElement), indexNum(index), left(lt), right(rt), height(h) {}
};

#endif // NODE_H