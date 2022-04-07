#ifndef SU20_HOFFMAN_PROJECT_RBTREE_H
#define SU20_HOFFMAN_PROJECT_RBTREE_H
#include "Tree.h"
#include "RedBlack.h"
#include <iostream>

using namespace std;

template <typename T>
class RBTree: public Tree<T> {
protected:
    RedBlack<T> rbTree;

public:
    RBTree();
    //RBTree(RBTree);
    ~RBTree();
    void insert(const T& x);
      //give insert definition for RBTree
    void print();
      //give print definition for RBTree
    bool contains(const T& x);
      //give contains definition for RBTree
    int containsWithCount(const T& x);
};

template <typename T>
RBTree<T>::RBTree() {
    //default constructor
}
/*
RBTree::RBTree(RBTree) {

}
*/
template <typename T>
RBTree<T>::~RBTree() {
      //destructor
}

template <typename T>
void RBTree<T>::insert(const T &x) {
    rbTree.insert(x);
}  //calls RedBlack insert function

template <typename T>
void RBTree<T>::print() {
    rbTree.print();
}  //calls RedBlack print function

template <typename T>
bool RBTree<T>::contains(const T &x) {
    return rbTree.contains(x);
}  //calls RedBlack contains function

template <typename T>
int RBTree<T>::containsWithCount(const T &x) {
    return rbTree.containsWithCount(x);
}

#endif //SU20_HOFFMAN_PROJECT_RBTREE_H
