#include "TreeTrie.h"


StatTrie::StatTrie(double anomalyRate){
    root = new Node;
    this->anomalyRate = anomalyRate;
    totalNodes = 1;
    totalChar = 0;
    totalUniqueWords = 0;
    totalWords = 0;
}

StatTrie::StatTrie(string filepath, double anomalyRate){
    ifstream file(filepath);

    if(!file.is_open()){
        throw runtime_error("Cannot open file: " + filepath);
    }

    string word;
    char c;

    while(file.get(c)){
        if(ignoredCharacters.count(c)) continue;

        if(delimiters.count(c)){
            if(!word.empty()){
                insert(word);
                word.clear();
            }
        }else{
            word.push_back(tolower(c));
        }
    }
    if(!word.empty()) insert(word);

    file.close();
}

StatTrie::~StatTrie(){
    delete root;
}



