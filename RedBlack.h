#ifndef SU20_HOFFMAN_PROJECT_REDBLACK_H
#define SU20_HOFFMAN_PROJECT_REDBLACK_H
#include "Node.h"
#include "Tree.h"
#include <iostream>

using namespace std;

template <typename T>
class RedBlack {
private:
    int numElements = 0;
    RedBlack(const RedBlack<T>&) {}

public:
    RedBlack();
    ~RedBlack();
    void insert(const T& x);
      //give insert definition for RBTree
    void insertFix(Node<T>* k);
      //for balancing the tree after insertion
    void print();
    void printHelper(Node<T>* root, string indent, bool last);
      //give print definition for RBTree
    bool contains(const T &x) const;
      //give contains definition for RBTree
    bool contains(const T &x, Node<T>*) const;
    int containsWithCount(const T &x) const;
    int containsWithCount(const T &x, Node<T>*) const;
    void leftRotate(Node<T>*);
    void rightRotate(Node<T>*);
    Node<T> minimum(Node<T> node);
    Node<T> maximum(Node<T> node);

    Node<T>* root;
};

template <typename T>
RedBlack<T>::RedBlack() {
    root = NULL;
}

template <typename T>
RedBlack<T>::~RedBlack() {

}

template <typename T>
void RedBlack<T>::insert(const T &key) {
    Node<T>* node = new Node<T>(key, NULL, NULL, "BLACK");
    node->parent = NULL;
    node->element = key;
    node->left = NULL;
    node->right = NULL;
    node->color = "RED";
      //sets a "blank" node with the value of key

    Node<T>* y = NULL;
    Node<T>* x = this->root;
      //sets x equal to the root of the tree

    while (x != NULL) {
        y = x;
        if (node->element < x->element) {
            x = x->left;
        } else {
            x = x->right;
        }
    }  //checks if node is the first element added to the tree

    node->parent = y;
    if (y == NULL) {
        root = node;
          //if statement checks if y has a parent node
    } else if (node->element < y->element) {
        y->left = node;
          //if node is less than parent, node goes to the left of the parent
    } else {
        y->right = node;
          //otherwise node goes to the right
    }

    if (node->parent == NULL) {
        node->color = "BLACK";
        return;
          //node is black if it has no parent and is therefore the root
    }

    if (node->parent->parent == NULL) {
        return;
    }

    insertFix(node);
      //runs after insertion of third element
}

template <typename T>
void RedBlack<T>::insertFix(Node<T>* k) {
      //function fixes tree and rotates it until balanced while changing color values
    Node<T>* u;
    while (k->parent->color == "RED") {
        if (k->parent == k->parent->parent->right) {
            u = k->parent->parent->left;
            if (u != NULL && u->color == "RED") {
                u->color = "BLACK";
                k->parent->color = "BLACK";
                k->parent->parent->color = "RED";
                k = k->parent->parent;
                 //sets color values of u, k, and k's parents if u is RED
            } else {
                if (k == k->parent->left) {
                    k = k->parent;
                    rightRotate(k);
                }
                k->parent->color = "BLACK";
                k->parent->parent->color = "RED";
                leftRotate(k->parent->parent);
            }  //does a right, then a left rotation if k equals the node to the left of it's parent
        } else {
            u = k->parent->parent->right;

            if (u != NULL && u->color == "RED") {
                u->color = "BLACK";
                k->parent->color = "BLACK";
                k->parent->parent->color = "RED";
                k = k->parent->parent;
                  //sets color values of u, k, and k's parents if u is RED
            } else {
                if (k == k->parent->right) {
                    k = k->parent;
                    leftRotate(k);
                }
                k->parent->color = "BLACK";
                k->parent->parent->color = "RED";
                rightRotate(k->parent->parent);
            }  //does a left, then a right rotation if k equals the node to the right of it's parent
        }
        if (k == root) {
            break;
        }  //breaks if k is equal to the root
    }
    root->color = "BLACK";
      //insures the color of the root is set to BLACK
}

template <typename T>
void RedBlack<T>::print() {
    if (root) {
        printHelper(this->root, "", true);
    }  //checks if tree is empty before using printhelper function to print tree
}

template <typename T>
void RedBlack<T>::printHelper(Node<T>* root, string indent, bool last) {
    if (root != NULL) {
        cout << indent;
        if (last) {
            cout << "R----";
            indent += "   ";
        } else {
            cout << "L----";
            indent += "|  ";
        }
          //prints R--- and L--- for right and left elements
        string sColor = root->color;
        //cout << root->element << "(" << sColor << ")" << endl;
          //prints color of the element
        printHelper(root->left, indent, false);
        printHelper(root->right, indent, true);
          //recursive call to go through entire tree
    }
}

template <typename T>
bool RedBlack<T>::contains(const T &x) const{
      //needs work
    return contains(x, root);
}

template <typename T>
int RedBlack<T>::containsWithCount(const T &x) const{
    return containsWithCount(x, root);
}

template <typename T>
bool RedBlack<T>::contains(const T &x, Node<T>* t) const {
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
int RedBlack<T>::containsWithCount(const T &x, Node<T> *t) const {
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
void RedBlack<T>::leftRotate(Node<T>* x) {
    Node<T>* y = x->right;
    x->right = y->left;
    if (y->left != NULL) {
        y->left->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == NULL) {
        this->root = y;
    } else if (x == x->parent->left) {
        x->parent->left = y;
    } else {
        x->parent->right = y;
    }
    y->left = x;
    x->parent = y;
}

template <typename T>
void RedBlack<T>::rightRotate(Node<T>* x) {
    Node<T>* y = x->left;
    x->left = y->right;
    if (y->right != NULL) {
        y->right->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == NULL) {
        this->root = y;
    } else if (x == x->parent->right) {
        x->parent->right = y;
    } else {
        x->parent->left = y;
    }
    y->right = x;
    x->parent = y;
}

template <typename T>
Node<T> RedBlack<T>::minimum(Node<T> node) {
    while (node->left != NULL) {
        node = node->left;
    }
    return node;
}

template <typename T>
Node<T> RedBlack<T>::maximum(Node<T> node) {
    while (node->right != NULL) {
        node = node->right;
    }
    return node;
}

#endif //SU20_HOFFMAN_PROJECT_REDBLACK_H
