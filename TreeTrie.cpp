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

void StatTrie::setIgnoredCharacters(const char* delim){
        for (int i = 0; delim[i] != '\0'; ++i)
        ignoredCharacters.insert(delim[i]);
}

void StatTrie::setDelimiters(const char* delim){
    for (int i = 0; delim[i] != '\0'; ++i)
        delimiters.insert(delim[i]);
}

void StatTrie::insert(string text){
    string word = "";

    for(char c : text){
        if(ignoredCharacters.find(c) != ignoredCharacters.end()) continue;

        if(delimiters.find(c) != delimiters.end()){
            if(!word.empty()){
                Node* cur = root;

                for(char ch : word){
                    if(cur->children.find(ch) == cur->children.end()){
                        cur->children[ch] = new Node();
                        totalNodes++;
                    }

                    cur = cur->children[ch];
                    cur->count++;
                }

                cur->isEndOfWord = true;
                totalWords++;
                totalUniqueWords++;
                totalChar += word.size();

                word.clear();
            }
        }else{
            word += c;
        }
    }

    if(!word.empty()){
        Node* cur = root;
        for(char ch : word){
            if(cur->children.find(ch) == cur->children.end()){
                cur->children[ch] = new Node();
                totalNodes++;
            }

            cur = cur->children[ch];
            cur->count++;

        }

        cur->isEndOfWord = true;
        totalWords++;
        totalUniqueWords++;
        totalChar += word.size();
    }

}

