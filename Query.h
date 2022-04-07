#ifndef QUERY_H
#define QUERY_H
#include "Tree.h"
#include "IndexWord.h"
#include <iostream>
#include <vector>

using namespace std;

class Query {
private:
    vector<string> userSearch;
    Tree<IndexWord> * queryIndex;
    vector<int> docCount;
    vector<int> sortedDocCount;
public:
    Query(Tree<IndexWord>* input);
    //default constructor
    void readQuery();
    //reads in query
    void parseQuery(char[]);
    //parses query
    void chooseSearch();
    //finds out if its an and/or/not/author search
    void andSearch();
    //runs search with and boolean operator
    void orSearch();
    //runs search with or boolean operator
    void notSearch();
    //runs search with not boolean operator
    void authorSearch();
    //runs search with author operator
    void seperateWords(string&, size_t&);
    //breaks up multi-word search and stores words in userSearch vector
    void getStats(Tree<IndexWord>*);
    //returns search statistics
    void getResults(vector<string>&docID);
    void sortCount(vector<string>&);
    void regSearch();
};

#endif // QUERY_H