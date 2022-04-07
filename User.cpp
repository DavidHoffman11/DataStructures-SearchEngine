#include "User.h"
#include "Tree.h"
#include "AVLTree.h"
#include "Query.h"
#include "AVL.h"
#include "IndexWord.h"
#include <iostream>
#include <dirent.h>
#include <string.h>
#include <stdio.h>
#include <string>
#include "DocParse.h"
#include "RedBlack.h"
#include "RBTree.h"

using namespace std;


User::User(char* argv[]) {
    commandLine = argv;
}

void User::start(char * argv[]) {
    int choice;

    cout << "----------SEARCH ENGINE----------" << endl;
    cout << "Choose an option:" << endl;
    cout << "1. Enter Search" << endl;
    cout << "2. Quit" << endl;
    cout << "Choice: ";
    cin >> choice;
    //displays initial menu and gets user input

    while(choice != 1 && choice != 2) {
        cout << "invalid choice, try again" << endl;
        cout << "Choose an option:" << endl;
        cout << "1. Enter Search" << endl;
        cout << "2. Quit" << endl;
        cout << "Choice: ";
        cin >> choice;
    }  //redisplays menu until choice = 1 or 2

    if(choice == 1) {
        interactiveMode(argv);
    }  //runs maintenance mode if choice = 1

    else if(choice == 2) {
        cout << "program exited";
        return;
    }  //runs interactive mode if choice = 2
}

void User::interactiveMode(char * argv[]) {
    int choice;
    char* option;

    cout << "----------SEARCH MODE----------" << endl;
    cout << "Choose an option:" << endl;
    cout << "1. Load index into AVL Tree" << endl;
    cout << "2. Load index into Red/Black Tree" << endl;
    cout << "Choice: ";
    cin >> choice;

    while(choice != 1 && choice != 2) {
        cout << "invalid choice, try again" << endl;
        cout << "Choose an option:" << endl;
        cout << "1. Load index into AVL Tree" << endl;
        cout << "2. Load index into Red/Black Tree" << endl;
        cout << "Choice: ";
        cin >> choice;
    }  //redisplays menu until choice = 1 or 2

    //AVL tree option
    if(choice == 1) {
        //index = new AVLIndex()
        DocParse parsingDocObj;
        index = parsingDocObj.readDoc(argv, 1);
        cout << "----------AVL Tree----------" << endl;
        cout << "Choose an option:" << endl;
        cout << "1. Enter Search Query" << endl;
        cout << "2. Print Search Statistics" << endl;
        cout << "3. Print AVL Tree" << endl;
        cout << "Choice: ";
        cin >> choice;

        while(choice != 1 && choice != 2 && choice != 3) {
            cout << "invalid choice, try again" << endl;
            cout << "Choose an option:" << endl;
            cout << "1. Enter Search Query" << endl;
            cout << "2. Print Search Statistics" << endl;
            cout << "3. Print AVL Tree" << endl;
            cout << "Choice: ";
            cin.ignore();
            cin.getline(option, 500);
            choice = atoi(option);
        }  //redisplays menu until choice = 1 or 2

        if(choice == 1) {
            Query q(index);
            q.readQuery();
        }  //creates query object & uses it to call the readQuery function

        else if(choice == 2) {
            Query q(index);
            q.getStats(index);
        }  //returns search statistics

        else if(choice == 3) {

        }
    }

        //Hash table option
    else if(choice == 2) {
        //index = new HashIndex();
        Tree<IndexWord> * paramPoint = index;
        DocParse parsingDocObj;
        paramPoint = parsingDocObj.readDoc(argv, 2);

        cout << "----------Red/Black Tree----------" << endl;
        cout << "Choose an option:" << endl;
        cout << "1. Enter Search Query" << endl;
        cout << "2. Print Search Statistics" << endl;
        cout << "Choice: ";
        cin >> choice;

        while(choice != 1 && choice != 2) {
            cout << "invalid choice, try again" << endl;
            cout << "Choose an option:" << endl;
            cout << "1. Enter Search Query" << endl;
            cout << "2. Print Search Statistics" << endl;
            cout << "Choice: ";
            cin >> choice;
        }  //redisplays menu until choice = 1 or 2

        if(choice == 1) {
            Query q(paramPoint);
            q.readQuery();
        }  //creates query object & uses it to call the readQuery function

        else if(choice == 2) {
            Query q(index);
            q.getStats(paramPoint);
        }  //returns search statistics
    }
}

Tree<IndexWord> & User::returnIndex() {
    return *index;
}
