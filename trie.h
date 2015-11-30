// This is start of the header guard.  
#ifndef TRIE_H
#define TRIE_H
 
// This is the content of the .h file, which is where the declarations go
#include <map>
struct Trie {
    map<char, Trie*> children;
    bool isEOW; /*
    bool hasChild(char key);
    bool hasWord(char* input, int length);
    void printAll(const string& prefix);
    void getAllWords(const string& prefix, vector<string>& results);
    void getRackWords(const string& prefix, map<char, int>& rack, vector<string>& results);
    void insert(char* input, int length);
    Trie(); */
};
 
// This is the end of the header guard
#endif