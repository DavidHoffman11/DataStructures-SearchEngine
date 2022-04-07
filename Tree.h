#ifndef TREE_H
#define TREE_H
#include <iostream>
#include <string>

using namespace std;

template <typename T>
class Tree {
public:
    //Tree() {}
      //default constructor
    virtual ~Tree() = default;
    virtual void insert(const T &x) = 0;
      //store data in hash table or avl tree
    // virtual bool contains(const T &x) = 0;
    virtual void print() = 0;
      //prints Tree
    virtual bool contains(const T &x) = 0;
      //checks if a variable x is in the tree
    virtual int containsWithCount(const T &x) = 0;

private:
    string s;
    Tree* r;
};

#endif // TREE_H
