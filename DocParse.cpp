#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include <algorithm>
#include <regex>
#include <string.h>
//#include "myhtml/api.h"
#include "DocParse.h"
//#include "regex.h"
#include "json.hpp"
#include "dirent.h"
#include "AVL.h"
#include <chrono>
#include <dirent.h>
#include <map>
#include <string>
#include "AVLTree.h"
#include "IndexWord.h"
#include "RBTree.h"
#include <vector>

using namespace std;
using json = nlohmann::json;
using namespace std::chrono;

DocParse::DocParse() {
    size = 0;
    //addStopWords();
    /*cout << "stop words are: " << endl;
    for(int i = 0; i < stopWords.size(); i++)
    {
        cout << stopWords[i] << endl;
    }*/
}

DocParse::~DocParse() {

}

Tree<IndexWord>* DocParse::readDoc(char *argv[], int structureChoice) {
    DIR *point;
    struct dirent *pointEnt;
    Tree<IndexWord>* p;
    Tree<IndexWord>* finalTree;

    string temp;
    vector<string> paperID;
    string fileText1;
    char fileText[500];
    json jObj;

    auto start = high_resolution_clock::now();
    //starts clock

    point = opendir(argv[1]);
    if (point != NULL) {
        int v = 0;
        while (v < 5) {
            pointEnt = readdir(point);
            string fileName = pointEnt->d_name;
            temp = argv[1];
            string fPath = temp + "/" + fileName;
            //cout << fPath << endl;
            ifstream file(fPath);

            if (fileName != "." && fileName != "..") {
                file >> jObj;
                //creates document object that'll eventually be added to the AVL tree
                if (jObj.find("paper_id") != jObj.end()) {
                    json paper_id = jObj["paper_id"];
                    temp = paper_id;
                    paperID.push_back(temp);
                }  //finds paperID and adds it to the doc obj
/* code to find other elements of document if necessarry
                if (jObj.find("metadata") != jObj.end()) {
                    json metadata = jObj["metadata"];
                    if (metadata.find("title") != metadata.end()) {
                        json title = jObj["title"];
                        if (title.find("") != title.end()) {
                            title1 = title;
                            newDoc.setTitle(title1);
                        }  //makes sure title isn't null
                    }  //finds title and adds it to the doc obj
                    if (metadata.find("authors") != metadata.end()) {
                        json authors = jObj["authors"];
                        if (authors.find("") != authors.end()) {
                            author = authors;
                            newDoc.setAuthor(author);
                        }
                    }  //finds author and adds it to the doc obj
                }
*/
                if (jObj.find("body_text") != jObj.end()) {
                    vector<json> body_text = jObj["body_text"];
                    for (int j = 0; j < 1; j++) {
                        if (body_text[j].find("text") != body_text[j].end()) {
                            json text = body_text[j]["text"];
                            //cout << text << endl;
                            fileText1 = text;
                            memcpy(fileText, fileText1.c_str(), 500);
                            //splits up text into singular words & removes stop words before adding words to documentWords

                            //splits up text into singular words & removes stop words before adding words to documentWords
                            vector<string> tempVec = removeStopWords(fileText);
                            copyVector(tempVec);
/*
                            map<string, map<string, int>>::iterator it = freq.find(paperID[0]);
                            if(it == freq.end()) {
                                pair<map<string, map<string, int>>::iterator, bool> newPair = freq.insert(
                                        make_pair(paperID[0], map<string, int>()));
                                it = newPair.first;
                            }
                            for(int y = 0; y < tempVec.size(); y++) {
                                //stemObj.stemWord(tempVec[y]);
                                docWords.push_back(tempVec[y]);

                                map<string, int>::iterator itr = it->second.find(tempVec[y]);
                                if(itr != it->second.end()) {
                                    itr->second = ++itr->second;
                                }
                                else {
                                    it->second.insert(make_pair(tempVec[y], 1));
                                }
                            }
*/
                        }
                    }
                }
                file.close();
            }
            v++;
        }
        if (structureChoice == 2) {
            p = stemDocWordstoRB(docWords);
        } else {
            p = stemDocWordstoAVL(docWords);
        }
        //finalTree = p;
        //finalTree->save();
        closedir(point);
    }
    return p;
}

void DocParse::copyVector(vector<string> x) {
    string temp;
    IndexWord newWord;

    for(int i = 0; i < x.size(); i++) {
        temp = x[i];
        newWord.setElement(temp);
        vector<IndexWord>::iterator it = find(docWords.begin(), docWords.end(), newWord);
        if(it == docWords.end()) {
            docWords.push_back(newWord);
        }
        else {
            it->increaseCount();
        }
    }
}

void DocParse::getDates(string &arr) {

    string s("Submitted");
    string d("Decided");
    std::size_t found = arr.find(s);
    std::size_t found2 = arr.find(".", found + 1, 6);
    cout << "Start: " << found << " End: " << found2 << endl;
    //submissionDate = arr.substr(found, found2-1);
    //cout << "Submission date is: " << submissionDate << endl;
}

void DocParse::addStopWords() {
    stopWords = {"i", "me", "my", "myself", "we", "our", "ours", "ourselves", "you", "your", "yours", "yourself", "yourselves", "he", "him", "his", "himself", "she", "her", "hers", "herself", "it", "its", "itself", "they", "them", "their", "theirs", "themselves", "what", "which", "who", "whom", "this", "that", "these", "those", "am", "is", "are", "was", "were", "be", "been", "being", "have", "has", "had", "having", "do", "does", "did", "doing", "a", "an", "the", "and", "but", "if", "or", "because", "as", "until", "while", "of", "at", "by", "for", "with", "about", "against", "between", "into", "through", "during", "before", "after", "above", "below", "to", "from", "up", "down", "in", "out", "on", "off", "over", "under", "again", "further", "then", "once", "here", "there", "when", "where", "why", "how", "all", "any", "both", "each", "few", "more", "most", "other", "some", "such", "no", "nor", "not", "only", "own", "same", "so", "than", "too", "very", "s", "t", "can", "will", "just", "don", "should", "now"};
}

void DocParse::sendToTree() {
    //string temp;
    AVL<string> TreeTree;
    //string temp;
    for (int i = 0; i < stemmedDocWords.size(); i++) {
        string temp;
        temp = stemmedDocWords[i];
        cout << "word is " << temp << endl;
        //TreeWord newObj(temp, docID);
        TreeTree.insert(temp);
        //TreeWord newObj(docID, temp);

        //tree.insert(newObj);
        //then add these to an AVL tree
    }
    TreeTree.print();
}

void DocParse::upperToLower(string &inputString) {
    //Turning all uppercase letters to lowercase with stl function
    //Referenced https://www.geeksforgeeks.org/conversion-whole-string-uppercase-lowercase-using-stl-c/
    transform(inputString.begin(), inputString.end(), inputString.begin(), ::tolower);
}

vector<string> DocParse::removeStopWords(char *arr) {
    //Adding all of the words that aren't stop words to the docWords vect

    vector<string>docWords;
    char *temp;
    temp = strtok(arr, ".-;:,?><='()[]& \n");
    while (temp != nullptr) {
        if (temp == nullptr) {
            continue;
        }
        string temp2 = temp;
        //addStopWords();
        upperToLower(temp2); //Need to make all lowercase before checking if a stop word
        if (find(stopWords.begin(), stopWords.end(), temp2) != stopWords.end()) {
            temp = strtok(nullptr, ".-;:,?><='()[]& \n");
            continue;
            //Don't want to do anything with this string as a stop word
        } else if (temp2.size() < 4) {
            temp = strtok(nullptr, ".-;:,?><='()[]& \n");
            continue;
            //do nothing if less than 3
        } else {
            docWords.push_back(temp2);
            //If not a stop word, it will add to the docWords vect
        }
        temp = strtok(nullptr, ".-;:,?><='()[]& \n");
    }

    return docWords;
}

bool DocParse::invalidChar(char c) {
    return !(c >= 0 && c < 128);
}

void DocParse::stripUnicode(string &str) {
    //str.erase(remove_if(str.begin(),str.end(), invalidChar), str.end());
}

AVLTree<IndexWord>* DocParse::stemDocWordstoAVL(vector<IndexWord> docWords) {
    //This function will take the documentWords (html tags and stop words already removed)
    //And will stem each word before adding it into a vector of all the stemmedDocWords
    //string temp; //Used to grab each Tree
    //StemFunctionality stemObj; //Will be used for stemming
    AVLTree<IndexWord>* p = new AVLTree<IndexWord>;
      //dynamically allocate

    for(int i = 0; i < docWords.size(); i++) {
        p->insert(docWords[i]);
    }
    /*
    for (int i = 0; i < docWords.size(); i++) {
        temp = docWords[i];
        //stemObj.stemWord(temp);
        TreeWord newTreeObj(temp, newDoc.getPaperID());
        if(p->contains(newTreeObj) != true) {
            p->insert(newTreeObj);
        }
        stemmedDocWords.push_back(temp);
    }

    map<string, map<string, int>>::iterator it = freq.begin();
    while(it != freq.end()) {
        map<string, int>::iterator itr = it->second.begin();
        while(itr != it->second.end()) {
            if(it->first != "") {
                string obj = it->first;
                p->insert(obj);
            }
            itr++;
        }
        it++;
    }
     */
    return p;

}


RBTree<IndexWord>* DocParse::stemDocWordstoRB(vector<IndexWord>docWords) {
    //This function will take the documentWords (html tags and stop words already removed)
    //And will stem each word before adding it into a vector of all the stemmedDocWords
    RBTree<IndexWord>* p = new RBTree<IndexWord>;
    //dynamically allocate

    for(int i = 0; i < docWords.size(); i++) {
        p->insert(docWords[i]);
    }

    return p;
}

int DocParse::getSize() {
    return size;
}


void DocParse::parseHTML(char *html) {

/*
    char html[] = "<div><span>HTML</span></div>";
        basic init
       myhtml_t* myhtml = myhtml_create();
       myhtml_init(myhtml, MyHTML_OPTIONS_DEFAULT, 1, 0);
       // first tree init
       myhtml_tree_t* tree = myhtml_tree_create();
       myhtml_tree_init(tree, myhtml);
       // parse html
       myhtml_parse(tree, MyENCODING_UTF_8, html, strlen(html));
       // print result
       // or see serialization function with callback: myhtml_serialization_tree_callback
       mycore_string_raw_t str = {0};
       myhtml_serialization_tree_buffer(myhtml_tree_get_document(tree), &str);
       //printf("%s\n", str.data);
       cout << "In html parser..." << endl << endl;
       string returner;
       //cout << str << endl;
       int htmlSize = sizeof(str);
       cout << "html size is: " << htmlSize << endl;
       for(int i = 0; i < htmlSize; i++)
       {
           returner = returner + str.data[i];
           cout << returner << endl;
       }
       // release resources
       mycore_string_raw_destroy(&str, false);
       myhtml_tree_destroy(tree);
       myhtml_destroy(myhtml);
       //str.data
       //cout << str.data[1] << endl;*/

}
/*
void DocParse::formatTitle(string &caseName) {
    string tempTitle;
    char word[caseName.length() + 1];
    strcpy(word, &caseName[0]);
    char *temp = strtok(word, "-");
    tempTitle = temp;
    temp = strtok(nullptr, "-/");
    while (temp != nullptr) {
        if (temp == nullptr) {
            continue;
        } else {
            tempTitle = tempTitle + " " + temp;
        }
        temp = strtok(nullptr, "-/");
    }
    title = tempTitle;
}
*/
AVL<string> &DocParse::getTreeTree() {
    return TreeTree;
}

void DocParse::printWords() {

}
