#ifndef SU20_HOFFMAN_PROJECT_INDEXWORD_H
#define SU20_HOFFMAN_PROJECT_INDEXWORD_H
#include <iostream>
#include <vector>

using namespace std;

class IndexWord {
private:
    string element;
    int count;

public:
    IndexWord();
    IndexWord(string x);
    vector<IndexWord> copyVector(vector<string> x);
    ~IndexWord();
    void setElement(string);
    void increaseCount();
    int getCount();
    IndexWord operator+(const IndexWord&);
    bool operator==(const IndexWord&) const;
    bool operator<(const IndexWord&) const;
    bool operator>(const IndexWord&) const;
};


#endif //SU20_HOFFMAN_PROJECT_INDEXWORD_H
