#include "IndexWord.h"
#include <iostream>
#include <cstring>

using namespace std;

IndexWord::IndexWord() {
    count = 1;
}

IndexWord::IndexWord(string x) {
    element = x;
    count = 1;
}

IndexWord::~IndexWord() {

}

void IndexWord::setElement(string x) {
    element = x;
}

void IndexWord::increaseCount() {
    count++;
}

int IndexWord::getCount() {
    return count;
}

IndexWord IndexWord::operator+(const IndexWord &x) {
    IndexWord result;
    int length;

    length = element.length() + x.element.length();

    result.element = new char[length+1];

    for(int i = 0; i < element.length(); i++) {
        result.element[i] = element[i];
    }

    for(int j = x.element.length(), i = 0; j < length; j++, i++) {

        this->element[j] = x.element[i];
    }

    return result;
}

bool IndexWord::operator==(const IndexWord &x) const {
    bool isSame = false;

    if (element.length() != x.element.length()) {
        return isSame;
    }

    for (int i = 0; i < x.element.length() + 1; i++) {
        if (element[i] == x.element[i]) {
            isSame = true;
        }  //checks if eqch element of word is equal to the corresponding element in data

        else {
            isSame = false;
            return isSame;
        }

    }

    return isSame;
}

bool IndexWord::operator<(const IndexWord &x) const {
    if((element < x.element) == true) {
        return true;
    }
    else{
        return false;
    }
}

bool IndexWord::operator>(const IndexWord &x) const {
    if((element > x.element) == true) {
        return true;
    }
    else{
        return false;
    }
}