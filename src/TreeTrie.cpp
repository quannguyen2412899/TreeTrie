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
    this->anomalyRate = anomalyRate;

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

void StatTrie::setIgnoredCharacters(const char* delim){
        for (int i = 0; delim[i] != '\0'; ++i)
        ignoredCharacters.insert(delim[i]);
}

void StatTrie::setDelimiters(const char* delim){
    for (int i = 0; delim[i] != '\0'; ++i)
        delimiters.insert(delim[i]);
}

void StatTrie::insert(string text){
    string word;

    for(char c : text){
        if(ignoredCharacters.count(c)) continue;

        if(delimiters.count(c)){
            if(!word.empty()){
                insertWord(word);
                word.clear();
            }
        }else{
            word.push_back(tolower(c));
        }
    }
    if(!word.empty()) insertWord(word);
}

void StatTrie::insertWord(const string& word){
    Node* cur = root;

    for(char c : word){
        if(cur->children.find(c) == cur->children.end()){
            cur->children[c] = new Node();
            totalNodes++;            
        }
        cur = cur->children[c];
        cur->count++;
    }

    if(!cur->isEndOfWord){
        cur->isEndOfWord = true;
        totalUniqueWords++;
    }
    totalWords++;
    totalChar += word.size();
}

bool StatTrie::insertFromFile(string filepath){
    ifstream file(filepath);

    if(!file.is_open()){
        cout << "Cannot open file:" << filepath << endl;
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

    if(!word.empty()){
        insert(word);
    }

    file.close();
    return true;
}

bool StatTrie::loadFromFile(string filepath){
    delete root;
    root = new Node();
    
    totalNodes = 1;       
    totalWords = 0;
    totalUniqueWords = 0;
    totalChar = 0;

    return insertFromFile(filepath);
}

bool StatTrie::contains(string word) const {
    Node* cur = root;

    for (char c : word) {
        auto it = cur->children.find(c);
        if (it == cur->children.end()) {
            return false;
        }
        cur = it->second;
    }
    return cur->isEndOfWord;
}

bool StatTrie::startWith(string prefix) const {
    Node* cur = root;

    for (char c : prefix) {
        auto it = cur->children.find(c);
        if (it == cur->children.end()) {
            return false;
        }
        cur = it->second;
    }
    return true;
}

void StatTrie::remove(string word){


}


unsigned int StatTrie::countNodes() const{
    return totalNodes;
}

unsigned int StatTrie::countCharacters() const{
    return totalChar;
}

unsigned int StatTrie::countWords() const{
    return totalWords;
}

unsigned int StatTrie::countUniqueWords() const{
    return totalUniqueWords;
}




