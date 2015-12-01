// This is start of the header guard.  
#ifndef MAP_I
#define MAP_I
#include <map>
#endif
#ifndef STRING_I
#define STRING_I
#include <string>
#endif
#ifndef VECTOR_I
#define VECTOR_I
#include <vector>
#endif
#ifndef IOSTREAM_I
#define IOSTREAM_I
#include <iostream>
#endif
#ifndef FSTREAM_I
#define FSTREAM_I
#include <fstream>
#endif

#ifndef TRIE_H
#define TRIE_H
using namespace std;
 
// This is the content of the .h file, which is where the declarations go
struct Trie {
    map<char, Trie*> children;
    bool isEOW;
    
    bool hasChild(char key){
        map<char, Trie*>::iterator result = children.find(key);
        return result != children.end();      
    }

    bool hasWord(char* input, int length){
        if (length == 0){
            return isEOW;
        }
        
        if (!hasChild(input[0])){
            return false;
        }
        
        return (children[input[0]])->hasWord(input+1, length-1);
    }
    
    void printAll(const string& prefix){
        if (isEOW){
            cout << prefix << endl;
        }
        
        for(map<char, Trie*>::iterator it = children.begin(); it != children.end(); it++){
            it->second->printAll(prefix + it->first);
        }
    }
    
    void getAllWords(const string& prefix, vector<string>& results){
        if (isEOW){
            results.push_back(prefix);
        }
        
        for(map<char, Trie*>::iterator it = children.begin(); it != children.end(); it++){
            it->second->getAllWords(prefix + it->first, results);
        }
    }
    
    void getRackWords(const string& prefix, map<char, int>& rack, vector<string>& results){
        if (isEOW){
            results.push_back(prefix);
        }
        
        for(map<char, Trie*>::iterator it = children.begin(); it != children.end(); it++){
            if (rack.find(it->first) != rack.end() && rack[it->first] > 0){
                    rack[it->first] -=1;
                    it->second->getRackWords(prefix + it->first, rack, results);
                    rack[it->first] +=1;
            }
        }
    }
    
    void insert(char* input, int length){
        if (length == 0){
            isEOW = true;
            return;
        }
        
        if (!hasChild(input[0])){
            Trie* newTrie = new Trie();
            children[input[0]] = newTrie;
        }

        (children[input[0]])->insert(input+1, length-1);
    }
    
    Trie(){
        isEOW = false;
    }
};
 
// This is the end of the header guard
#endif