#include "Query.h"
#include "DocParse.h"
#include "User.h"
#include <iostream>
#include <algorithm>
#include <vector>
#include <map>

using namespace std;

Query::Query(Tree<IndexWord> * input) {
    //default constructor
    queryIndex = input;
}

void Query::readQuery() {
    char search[500];

    cout << "----------SEARCH QUERY----------" << endl;
    cout << "Rules of search:" << endl;
    cout << "1. Multi-word searches must be prefixed with a boolean operator (AND,OR)" << endl;
    cout << "2. No query can have both AND and  OR" << endl;
    cout << "3. Search terms may be preceded with a NOT operator" << endl;
    cout << "4. You may include the AUTHOR operator followed by an author name to return documents from that author" << endl;
    cout << "Enter search: ";
    cin.ignore();
    cin.getline(search, 500);
    //prints menu and stores user search in a string
    string temp = search;
    userSearch.push_back(temp);

    //parseQuery(search); only necessary for multiple word searches
    //stems search and stores each individual word in the userSearch vector
    chooseSearch();
    //checks for AND, OR, NOT, or AUTHOR operators and adjusts search accordingly
}

void Query::chooseSearch() {
    if(userSearch.size() < 2) {
        regSearch();
    }  //immediately does a regular search if the search is only one word
/*
    for(int i = 0; i < userSearch.size(); i++) {
        if(userSearch[i] == "or") {
            orSearch();
        }  //runs orSearch if "or" is found
        else if(userSearch[i] == "and") {
            andSearch();
        }
        else if(userSearch[i] == "not") {
            notSearch();
        }
        else if(userSearch[i] == "author") {
            authorSearch();
        }
        else {
            regSearch();
        }  //runs andSearch if "or" isn't found
    }
*/
}

void Query::regSearch() {
    IndexWord search;
    search.setElement(userSearch[0]);
      //turns search into an IndexWord object

    if(queryIndex->contains(search) == true) {
        cout << userSearch[0] << " found " << queryIndex->containsWithCount(search) << " time(s)" << endl;
    }

    else {
        cout << "Word not found" << endl;
    }
}

void Query::getStats(Tree<IndexWord>* index) {
    cout << "----------SEARCH STATS----------" << endl;
    cout << "Number of documents indexed: 10" << endl;
    cout << "Total number of unique words: " << endl;
    cout << "Average number of words indexed per opinion: " << endl;
    cout << "Top 50 most frequent words: " << endl;
}
/*
void Query::sortCount(vector<int> docUnions) {
    for(int i = 0; i < docUnions.size(); i++) {
    }
}

void Query::getResults(vector<string> &docID) {
    IndexWord w;
    vector<Document> d = w.getDocVect();
    vector<string> topHits;
    vector<Document> temp;

    for(int i = 0; i < 15; i++) {
        for(int j = 0; j < docCount.size(); j++) {
            if(sortedDocCount[i] == docCount[j]) {
                topHits.push_back(docID[j]);
            }
        }
    }

    for(int i = 0; i < topHits.size(); i++) {
        for(int j = 0; j < d.size(); j++) {
            if(topHits[i] == d[j].getTitle()) {
                temp.push_back(d[j]);
            }
        }
    }

    cout << "----------SEARCH Results----------" << endl;
    for(int i = 0; i < 15; i++) {
        cout << "Result: " << i+1 << endl;
        cout << "Title: " << temp[i].getTitle() << endl;
    }
}

void Query::sortCount(vector<string> &docID) {
    IndexWord w;
    vector<Document> d = w.getDocVect();
    //vector<Document> sortedInfo;

    for(int i = 0; i < docID.size(); i++) {
        for(int j = 0; j < d.size(); i++) {
            if(d[j].getTitle() == docID[i]) {
                docCount.push_back(d[j].getDocCount());
            }
        }
    }

    sortedDocCount = docCount;

    sort(sortedDocCount.begin(), sortedDocCount.end(), greater<int> ());
}


void Query::andSearch() {
    vector<vector<Document>> docInfo;
    vector<string> docUnions;
    vector<string>::iterator it;

    for(int i = 0; i < userSearch.size(); i++)
    {
        if(userSearch[i] == "not") {
            break;
        }

        string tempInput = userSearch[i];
        IndexWord tempIndexWord(tempInput);
        if(queryIndex->contains(tempIndexWord))
        {
            IndexWord indexObj2 = queryIndex->find(tempIndexWord);
            vector<Document> temp2 = indexObj2.getDocVect();
            docInfo.push_back(temp2);
        }
    }
    for(int z =0; z < docInfo.size(); z++)
    {
        //Document printingDoc = docInfo[z];
    }
    for(int i = 1; i < docInfo.size() -1; i++) {
        vector<Document> temp = docInfo[i-1];
        vector<Document> temp1 = docInfo[i];
        vector<string> temp2;
        vector<string> temp3;
        vector<string> temp4;

        for(int i = 0; i< docInfo.size(); i++) {
            temp3[i] = temp[i].getTitle();
            temp4[i] = temp1[i].getTitle();
        }

        it = set_intersection(temp3.begin(), temp3.end(), temp4.begin(), temp4.end(), temp2.begin());

        for(int j = 0; j < temp2.size(); j++) {
            if(count(docUnions.begin(), docUnions.end(), temp2[i])) {
                //does nothing if docID is already in vector
            }

            else {
                docUnions.push_back(temp2[i]);
            }
        }
    }

    sortCount(docUnions);
    getResults(docUnions);
}

void Query::orSearch() {
    vector<vector<Document>> docInfo;
    vector<string> docUnions;
    vector<string>::iterator it;

    for(int i = 0; i < userSearch.size(); i++)
    {
        if(userSearch[i] == "not") {
            break;
        }

        string tempInput = userSearch[i];
        IndexWord tempIndexWord(tempInput);
        if(queryIndex->contains(tempIndexWord))
        {
            IndexWord indexObj2 = queryIndex->find(tempIndexWord);
            vector<Document> temp2 = indexObj2.getDocVect();
            docInfo.push_back(temp2);
        }
    }

    for(int i = 1; i < docInfo.size()-1; i++) {
        vector<Document> temp = docInfo[i-1];
        vector<Document> temp1 = docInfo[i];
        vector<string> temp2;
        vector<string> temp3;
        vector<string> temp4;

        for(int i = 0; i< docInfo.size(); i++) {
            temp3[i] = temp[i].getTitle();
            temp4[i] = temp1[i].getTitle();
        }

        it = set_union(temp3.begin(), temp3.end(), temp4.begin(), temp4.end(), temp2.begin());

        for(int j = 0; j < temp2.size(); j++) {
            if(count(docUnions.begin(), docUnions.end(), temp2[i])) {
                //does nothing if docID is already in vector
            }

            else {
                docUnions.push_back(temp2[i]);
            }
        }

    }

    sortCount(docUnions);
    getResults(docUnions);
}

void Query::notSearch() {

}

void Query::authorSearch() {

}

void Query::parseQuery(char search[500]) {
    DocParse d;
    StemFunctionality stemObj;
    //IndexWord output;
    char *temp;

    temp = strtok(search, ".-;:,?><='()[]& \n");
    string temp1 = temp;

    d.upperToLower(temp1);
    stemObj.stemWord(temp1);
    userSearch.push_back(temp1);
    //output.getIndexWord(temp1);
    temp = strtok(nullptr, ".-;:,?><='()[]& \n");

    while (temp != nullptr) {
        if (temp == nullptr) {
            continue;
        }
        string temp2 = temp;
        d.upperToLower(temp2);
        stemObj.stemWord(temp2);
        userSearch.push_back(temp2);
        temp = strtok(nullptr, ".-;:,?><='()[]& \n");
    }
}
*/