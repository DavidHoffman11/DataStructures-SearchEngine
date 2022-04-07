#ifndef DOCPARSE_H
#define DOCPARSE_H
#include "AVL.h"
#include "Tree.h"
#include "AVLTree.h"
#include "RBTree.h"
#include "IndexWord.h"
#include <dirent.h>
//#include <myhtml/api.h>
//#include <myhtml/api.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

using namespace std;
class DocParse
{
public:
    DocParse();
    ~DocParse();
    Tree<IndexWord>* readDoc(char **argv, int choice);
    void copyVector(vector<string> x);
    void parseHTML(char * html);
    void printWords();
    void addStopWords();
    vector<string> removeStopWords(char * arr);
    AVLTree<IndexWord>* stemDocWordstoAVL(vector<IndexWord>);
    RBTree<IndexWord>* stemDocWordstoRB(vector<IndexWord>);
    void upperToLower(string & );
    void sendToTree();
    void formatTitle(string &);
    void getDates(string & arr);
    AVL<string>& getTreeTree();
    int getSize();
    bool invalidChar(char c);
    void stripUnicode(string & str);
    //returns TreeTree

private:
    int size;
    vector<string> stopWords = {"i", "me", "my", "myself", "we", "our", "ours", "ourselves", "you", "your", "yours", "yourself", "yourselves", "he", "him", "his", "himself", "she", "her", "hers", "herself", "it", "its", "itself", "they", "them", "their", "theirs", "themselves", "what", "which", "who", "whom", "this", "that", "these", "those", "am", "is", "are", "was", "were", "be", "been", "being", "have", "has", "had", "having", "do", "does", "did", "doing", "a", "an", "the", "and", "but", "if", "or", "because", "as", "until", "while", "of", "at", "by", "for", "with", "about", "against", "between", "into", "through", "during", "before", "after", "above", "below", "to", "from", "up", "down", "in", "out", "on", "off", "over", "under", "again", "further", "then", "once", "here", "there", "when", "where", "why", "how", "all", "any", "both", "each", "few", "more", "most", "other", "some", "such", "no", "nor", "not", "only", "own", "same", "so", "than", "too", "very", "s", "t", "can", "will", "just", "don", "should", "now"};
    vector<string> stemmedDocWords;
    vector<IndexWord> docWords;
    string docID;
    AVL<string> TreeTree;
    map<string, int> m;
    map<string, map<string, int>> freq;
};

#endif // DOCPARSE_H
