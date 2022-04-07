#ifndef USER_H
#define USER_H
#include "Tree.h"
#include "AVLTree.h"
#include "DocParse.h"
#include "AVL.h"
#include "IndexWord.h"

class User {
private:
    Tree<IndexWord>* index;
    char ** commandLine;
public:
    User(char * argv[]);
    //default constructor
    void exploreDir(char * dir_name, char** argv);
    void start(char * argv[]);
    //starts program
    void maintenanceMode(char **);
    //runs maintenance mode
    void interactiveMode(char **);
    //runs interactive mode
    Tree<IndexWord> & returnIndex();
    void startDemo(AVL<IndexWord>, char**);
};

#endif // USER_H
