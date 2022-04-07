#ifndef SU20_HOFFMAN_PROJECT_TEST_H
#define SU20_HOFFMAN_PROJECT_TEST_H
#include "AVLTree.h"
#include <iostream>

using namespace std;

class Test {
public:
    Test();
    ~Test();
    bool testAVL();
      //return true if AVL works properly
    bool testRedBlack();
      //return true if Red/Black Tree works properly
    bool testSplay();
      //return true if Splay Tree works properly
};

#endif //SU20_HOFFMAN_PROJECT_TEST_H
