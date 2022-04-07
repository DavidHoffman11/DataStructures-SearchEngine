#ifndef AVLINDEX_H
#define AVLINDEX_H
#include "Tree.h"
#include "AVL.h"
#include <vector>
#include <iostream>

using namespace std;

template <typename T>
class AVLTree: public Tree<T> {
protected:
    AVL<T> avlTree;

public:
    AVLTree();
    //default constructor
    AVLTree(vector<T>);
    ~AVLTree();
    //destructor
    void insert(const T& x);
    //give insert definition for avl
    void print();
    //give print definition for avl
    bool contains(const T &x);
    int containsWithCount(const T &x);
    T& find(T & x);
    //give contains definition for avl
    //bool contains(const string & x);
    AVL<T>& returnAVLTree();
    string toString(Node<T> *t);
    void save();
};

template <typename T>
AVLTree<T>::AVLTree() {

}

template <typename T>
AVLTree<T>::AVLTree(vector<T> x) {

}

template <typename T>
AVLTree<T>::~AVLTree() {
    avlTree.makeEmpty();
    //makes the tree logically empty
    // avlTree.~AVL();
    //frees up memory
}

template <typename T>
void AVLTree<T>::insert(const T& x) {
    avlTree.insert(x);
}

template <typename T>
void AVLTree<T>::print() {
    avlTree.print();
}

template <typename T>
T& AVLTree<T>::find(T&x)
{
    return avlTree.find(x);
}

template <typename T>
AVL<T> & AVLTree<T>::returnAVLTree()
{
    return avlTree;
}

template <typename T>
bool AVLTree<T>::contains(const T &x) {
    return avlTree.contains(x);
}

template <typename T>
int AVLTree<T>::containsWithCount(const T &x) {
    return avlTree.containsWithCount(x);
}
/*
string AVLTree::toString(AVLNode<string> *t) {

    if(t == nullptr) {
        return "";
    }
    string temp;
    temp += toString(t->left) + t->element.getIndexWord() + " " + toString(t->right);
    return temp;

} //end save
*/
template <typename T>
void AVLTree<T>::save() {
    ofstream file;
    file.open("AVLOutput.txt");
    if(! file.is_open()) {
        cout << "File didnt open" << endl;
    }
    file<<toString(avlTree.root);
}



/*bool AVLTree::contains(const string &x)
{
    return avlTree.contains(x);
}*/

//class provides avl definitions for abstract index classes

#endif // AVLINDEX_H
