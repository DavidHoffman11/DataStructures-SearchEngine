#ifndef SU20_HOFFMAN_PROJECT_STREE_H
#define SU20_HOFFMAN_PROJECT_STREE_H
#include "Tree.h"
#include "Splay.h"
#include <iostream>

using namespace std;

template <typename T>
class STree: public Tree<T> {
protected:
    Splay<T> sTree;

public:
    STree();
    //STree(STree);
    ~STree();
    void insert(const T& x);
      //give insert definition for STree
    void print();
      //give print definition for STree
    bool contains(const T& x);
      //give contains definition for STree
};

template <typename T>
STree<T>::STree() {
    //default constructor
}
/*
STree::STree(STree) {

}
*/
template <typename T>
STree<T>::~STree() {

}

template <typename T>
void STree<T>::insert(const T &x) {
    sTree.insert(x);
}

template <typename T>
void STree<T>::print() {
    sTree.print();
}

template <typename T>
bool STree<T>::contains(const T &x) {
    return sTree.contains(x);
}

#endif //SU20_HOFFMAN_PROJECT_STREE_H
