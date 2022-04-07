#include "Test.h"
#include "AVLTree.h"
#include "RBTree.h"
#include "IndexWord.h"
#include "STree.h"
#include <iostream>

using namespace std;

Test::Test() {

}

Test::~Test() {

}

bool Test::testAVL() {
    AVLTree<IndexWord> newTree;
    IndexWord word;
    word.setElement("Hi");

    newTree.insert(word);


    if(newTree.contains(word) == false) {
        return false;
    }

    return true;
}

bool Test::testRedBlack() {
    RBTree<IndexWord> newTree;
    IndexWord word;
    word.setElement("Hi");

    newTree.insert(word);

    if(newTree.contains(word) == false) {
        return false;
    }

    return true;
}

bool Test::testSplay() {

    return true;
}