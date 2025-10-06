#ifndef _TREETRIE_
#define _TREETRIE_


#include <iostream>
#include <unordered_map>
#include <vector>
#include <unordered_set>
#include <fstream>
using namespace std;


// Statistical trie
class StatTrie {

    private:

    struct Node {
        unordered_map<char, Node*> children;
        int count;
        bool isEndOfWord;

        Node() : count(0), isEndOfWord(false){}
        ~Node(){
            for(auto& p: children)
                delete p.second;
        };
    };

    Node* root;
    unordered_set<char> ignoredCharacters;   // Set of characters that will be ingored eg. ignore '-':  "sub-tree" => "subtree" 
    unordered_set<char> delimiters;    // Set of characters that seperate words
    double anomalyRate;  // The appearance rate of one word below this rate => anomaly
    unsigned int totalNodes, totalUniqueWords;
    unsigned int totalChar, totalWords;


    public:

    StatTrie(double anomalyRate = 0.001);
    StatTrie(string filepath, double anomalRate = 0.001);  // Construct from a text file
    ~StatTrie();
    
    void setIgnoredCharacters (const char* delim);
    void setDelimiters (const char* delim);
    void insert (string text);
    void insertWord(const string& word);    //Helper
    bool insertFromFile (string filepath);  // Insert data from another file (no overwriting)
    bool loadFromFile (string filepath);    // Load data from another file (overwrite)
    bool contains (string words) const;
    bool startWith (string prefix) const;
    void remove (string word);
    void clear();

    unsigned int countNodes() const;
    unsigned int countCharacters() const;
    unsigned int countWords() const;
    unsigned int countUniqueWords() const;

    void setAnomalyRate (double rate);
    double frequency (string word) const;
    bool isAnomalyWord (string word) const;
    //bool isAnomalyPrefix (string prefix);
    vector<string> getAnomalies() const;

    void writeStatistic (string filepath) const;  // Write statistics to file
    void visualize() const;   // Visualize trie
};


#endif
