#include "Test.h"
#include "DocParse.h"
#include "User.h"
#include <iostream>

using namespace std;

int main (int argc, char *argv[]) {
    Test t;
    DocParse d;
    User start(argv);

    if(t.testAVL() == false) {
        return -1;
    }

    else if(t.testRedBlack() == false) {
        return -1;
    }

    else if(t.testSplay() == false) {
        return -1;
    }

    start.start(argv);

    return 0;
}

