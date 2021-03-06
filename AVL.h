#ifndef AVL_H
#define AVL_H
#include "Node.h"
#include "Tree.h"
#include "IndexWord.h"
#include <iostream>
#include <fstream>

using namespace std;

template <typename T>
class AVL {
private:

    int numElements = 0;

public:
    Node<T>* root;
    AVL() : root(NULL) {}
    //default contructor
    /* AVL(const AVL<T> &rhs) : root(nullptr) {
         *this = root;
     }  //copy constructor*/
    /* AVL(const AVL<T> &rhs) : root(nullptr) {
        *this = root;
    }  //copy constructor */
    ~AVL();
    //destructor
    const T& findMin() const;
    Node<T>* findMin(Node<T>*) const;
    //finds the smallest element in the tree
    Node<T>* findMax(Node<T>* t) const;
    const T& findMax() const;
    //finds the biggest element in the tree
    bool contains(const T &x, Node<T>* t) const;
    //bool contains(const T &x, Node<IndexWord>* t) const;
    bool contains(const T &x) const;
    //returns true if the element is in the tree
    int containsWithCount(const T &x, Node<T>* t) const;
    int containsWithCount(const T &x) const;
    bool isEmpty() const;
    //returns true if the tree is empty
    void makeEmpty(Node<T>* &t);
    void makeEmpty();
    //makes the tree logically empty
    void insert(const T &x);
    void insert(const T &x, Node<T>* &t);
    //inserts elements into the tree
    void rotateWithLeftChild(Node<T>* &x);
    void rotateWithRightChild(Node<T>* &x);
    void doubleWithLeftChild(Node<T>* &x);
    void doubleWithRightChild(Node<T>* &x);
    T& find(T, Node<T>* &x);
    T& find(T);
    int height(Node<T>* t) const;
    //returns height
    int max(int lhs, int rhs) const;
    //returns max
    int getNumElements();
    //returns the number of elements in the tree
    //saves tree to local disk
    Node<T>* clone(Node<T> *t) const;
    //clones avl tree
    const AVL& operator= (const AVL&);
    //overloaded equals operator
    void print() const;
    void printTree(Node<T>* t) const;
    //prints the tree
    void save();
};

template <typename T>
AVL<T>::~AVL() {
    makeEmpty();
}

template <typename T>
Node<T>* AVL<T>::clone(Node<T>* t) const {
    if(t == nullptr) {
        return nullptr;
    }

    else {
        return new Node<T>(t->element, clone(t->left), clone(t->right), t->height);
    }
}

template <typename T>
const T& AVL<T>::findMin() const {
    if(isEmpty()) {
        return 0;
    }

    return findMin(root)->element;
}

template <typename T>
Node<T>* AVL<T>:: findMin(Node<T>* t) const {
    if(t == nullptr) {
        return nullptr;
    }
    else if(t->left == nullptr) {
        return t;
    }

    return findMin(t->left);
}

template <typename T>
Node<T>* AVL<T>::findMax(Node<T>* t) const {
    if(t != nullptr) {
        while(t->right != nullptr) {
            t = t->right;
        }
    }

    return t;
}

template <typename T>
bool AVL<T>::contains(const T &x) const {
    return contains(x, root);
}

template <typename T>
int AVL<T>::containsWithCount(const T &x) const {
    return containsWithCount(x, root);
}
/*
template <typename T>
bool AVL<T>::contains(const T &x, Node<IndexWord>* t) const {
    if(t == nullptr) {
        return false;
    }  //returns false if tree is empty
    else if(x < t->element.getIndexWord()) {
        return contains(x, t->left);
    }
    else if(t->element.getIndexWord() < x) {
        return contains(x, t->right);
    }
    else {
        return true;
    }
}
*/
template <typename T>
bool AVL<T>::contains(const T &x, Node<T>* t) const {
    if(t == nullptr) {
        return false;
    }  //returns false if tree is empty

    else if(t->element > x) {
        return contains(x, t->left);
    }

    else if(t->element < x) {
        return contains(x, t->right);
    }

    else {
        return true;
    }
}

template <typename T>
int AVL<T>::containsWithCount(const T &x, Node<T> *t) const {
    if(t == nullptr) {
        return 0;
    }  //returns false if tree is empty

    else if(t->element > x) {
        return containsWithCount(x, t->left);
    }

    else if(t->element < x) {
        return containsWithCount(x, t->right);
    }

    else {
        IndexWord word = t->element;
        return word.getCount();
    }
}

template <typename T>
bool AVL<T>::isEmpty() const {
    return root == nullptr;
}

template <typename T>
void AVL<T>::makeEmpty() {
    makeEmpty(root);
}

template <typename T>
void AVL<T>::makeEmpty(Node<T>* &t) {
    if(t != nullptr) {
        makeEmpty(t->left);
        makeEmpty(t->right);
        delete t;
    }
    t = nullptr;
}

template <typename T>
void AVL<T>::insert(const T &x) {
    insert(x, root);
}

template <typename T>
void AVL<T>::insert(const T &x, Node<T>* &t) {
    //cout << "Inserting..." << endl;
    if(t == nullptr) {
        //cout << "Node is empty" << endl;
        t = new Node<T>(x,nullptr,nullptr);
        numElements++;
    }  //checks if node is empty

    else if(t->element > x) {
        insert(x, t->left);
        if(height(t->left) - height(t->right) == 2) {
            if(t->left->element > x) {
                rotateWithLeftChild(t);
            }  //case 1

            else {
                doubleWithLeftChild(t);
            }  //case 2
        }
    }
    else if(t->element < x) {
        //cout << "Node inserting is greater than" << endl;
        insert(x, t->right);
        if(height(t->right) - height(t->left) == 2) {
            if(t->right->element < x) {
                rotateWithRightChild(t);
            }  //case 4

            else {
                doubleWithRightChild(t);
            }  //case 3
        }
    }

    else {
        // cout << "In final else..." << endl;
        t->element = t->element + x;
    }

    t->height = max(height(t->left), height(t->right) + 1);
}

template <typename T>
void AVL<T>::rotateWithLeftChild(Node<T>* &k2) {
    Node<T>* k1 = k2->left;
    k2->left = k1->right;
    k1->right = k2;

    k2->height = max(height(k2->left), height(k2->right)) + 1;
    k1->height = max(height(k1->left), k2->height) + 1;
    k2 = k1;
}

template <typename T>
void AVL<T>::rotateWithRightChild(Node<T>* &k2) {
    Node<T>* k1 = k2->right;
    k2->right = k1->left;
    k1->left = k2;

    k2->height = max(height(k2->left), height(k2->right)) + 1;
    k1->height = max(height(k1->left), k2->height) + 1;
    k2 = k1;
}

template <typename T>
void AVL<T>::doubleWithLeftChild(Node<T>* &k3) {
    rotateWithRightChild(k3->left);
    rotateWithLeftChild(k3);
}

template <typename T>
void AVL<T>::doubleWithRightChild(Node<T>* &k3) {
    rotateWithLeftChild(k3->right);
    rotateWithRightChild(k3);
}

template <typename T>
int AVL<T>::height(Node<T>* t) const {
    if(t == nullptr) {
        return -1;
    }  //return -1 if null

    else {
        return t->height;
    }  //returns height if its not null
}

template <typename T>
int AVL<T>::max(int lhs, int rhs) const {
    return lhs > rhs ? lhs : rhs;
}

template <typename T>
T& AVL<T>::find(T word) {
    return find(word, root);
}

template <typename T>
T& AVL<T>::find(T word, Node<T>* &t) {
    if(t == nullptr) {
        cout << "tree is empty" << endl;
    }  //returns false if tree is empty

    else if(t->element > word ) {
        return find(word, t->left);
    }

    else if(t->element < word) {
        return find(word, t->right);
    }

    return t->element;
}

template <typename T>
int AVL<T>::getNumElements() {
    return numElements;
}

template <typename T>
const AVL<T>& AVL<T>::operator=(const AVL<T>& rhs) {
    if(this != &rhs) {
        makeEmpty();
        root = clone(rhs.root);
    }

    return *this;
}

template <typename T>
void AVL<T>::print() const {
    if(isEmpty()) {
        cout << "The tree is Empty" << endl;
    }

    else {
        printTree(root);
    }
}

template <typename T>
void AVL<T>::printTree(Node<T>* t) const {
    if(t != nullptr) {
        printTree(t->left);
        //cout << t->element << endl;
        printTree(t->right);
    }
}

template <typename T>
void AVL<T>::save() {

}

#endif // AVL_H
