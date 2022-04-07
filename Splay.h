#ifndef SU20_HOFFMAN_PROJECT_SPLAY_H
#define SU20_HOFFMAN_PROJECT_SPLAY_H
#include "Node.h"
#include "Tree.h"
#include <iostream>

using namespace std;

template <typename T>
class Splay {
private:
    int numElements = 0;
    Splay(const Splay<T>&) {}

public:
    Splay();
    ~Splay();
    void insert(const string& x);
      //give insert definition for STree
    Node<T>* find(const T &key);
    void print();
      //give print definition for STree
    bool contains(const string &x);
      //give contains definition for STree
    void right_Rotate(Node<T>*x);
    void left_Rotate(Node<T>*x);
    void splay(Node<T>*x);
    void replace(Node<T> *u, Node<T> *v);
    Node<T>* subtree_minimum(Node<T> *u);
    Node<T>* subtree_maximum(Node<T>* u);
    void erase(const T &key);

    Node<T>* root;
};

template <typename T>
Splay<T>::Splay() {
    root = NULL;
}

template <typename T>
Splay<T>::~Splay() {

}

template <typename T>
void Splay<T>::insert(const string &key) {
    Node<T> *z = root;
    Node<T> *p = NULL;

    while (z) {
        p = z;
        if (z->element < key) {
            z = z->right;
        }
        else z = z->left;
    }

    z = new Node<T>(key);
    z->parent = p;

    if (!p) root = z;
    else if (p->element < z->element) {
        p->right = z;
    }
    else p->left = z;

    splay(z);
    p->height++;
}

template <typename T>
Node<T>* Splay<T>::find(const T &key) {
    Node<T> *z = root;
    while (z) {
        if (comp(z->element, key)) z = z->right;
        else if (comp(key, z->element)) z = z->left;
        else return z;
    }
    return NULL;
}

template <typename T>
void Splay<T>::print() {

}

template <typename T>
bool Splay<T>::contains(const string &x) {

    return false;
}

template <typename T>
void Splay<T>::left_Rotate(Node<T> *x) {
    Node<T> *y = x->right;
    if (y) {
        x->right = y->left;
        if (y->left) y->left->parent = x;
        y->parent = x->parent;
    }

    if (!x->parent) root = y;
    else if (x == x->parent->left) x->parent->left = y;
    else x->parent->right = y;
    if (y) y->left = x;
    x->parent = y;
}

template <typename T>
void Splay<T>::right_Rotate(Node<T> *x) {
    Node<T> *y = x->left;
    if (y) {
        x->left = y->right;
        if (y->right) y->right->parent = x;
        y->parent = x->parent;
    }
    if (!x->parent) root = y;
    else if (x == x->parent->left) x->parent->left = y;
    else x->parent->right = y;
    if (y) y->right = x;
    x->parent = y;
}

template <typename T>
void Splay<T>::splay(Node<T> *x) {
    while (x->parent) {
        if (!x->parent->parent) {
            if (x->parent->left == x) right_Rotate(x->parent);
            else left_Rotate(x->parent);
        } else if (x->parent->left == x && x->parent->parent->left == x->parent) {
            right_Rotate(x->parent->parent);
            right_Rotate(x->parent);
        } else if (x->parent->right == x && x->parent->parent->right == x->parent) {
            left_Rotate(x->parent->parent);
            left_Rotate(x->parent);
        } else if (x->parent->left == x && x->parent->parent->right == x->parent) {
            right_Rotate(x->parent);
            left_Rotate(x->parent);
        } else {
            left_Rotate(x->parent);
            right_Rotate(x->parent);
        }
    }
}

template <typename T>
void Splay<T>::replace(Node<T> *u, Node<T> *v) {
    if (!u->parent) root = v;
    else if (u == u->parent->left) u->parent->left = v;
    else u->parent->right = v;
    if (v) v->parent = u->parent;
}

template <typename T>
Node<T>* Splay<T>::subtree_minimum(Node<T> *u) {
    while (u->left) u = u->left;
    return u;
}

template <typename T>
Node<T>* Splay<T>::subtree_maximum(Node<T> *u) {
    while (u->right) u = u->right;
    return u;
}

template <typename T>
void Splay<T>::erase(const T &key) {
    Node<T> *z = find(key);
    if (!z) return;

    splay(z);

    if (!z->left) replace(z, z->right);
    else if (!z->right) replace(z, z->left);
    else {
        Node<T> *y = subtree_minimum(z->right);
        if (y->parent != z) {
            replace(y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        replace(z, y);
        y->left = z->left;
        y->left->parent = y;
    }

    delete z;
    //p.height--;
}

#endif //SU20_HOFFMAN_PROJECT_SPLAY_H