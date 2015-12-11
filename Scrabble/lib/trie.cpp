#include <fstream>
#include <iostream>
#include <string>
#include <vector>
//#include "../lib/structs.cpp"
#include "../lib/weight.cpp"
#include <fstream>
using namespace std;
//Sam. completed to return all words that can be made by the letters in your rack, including a wildcard

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
          //object it in chilren
        for(map<char, Trie*>::iterator it = children.begin(); it != children.end(); it++){
            it->second->getAllWords(prefix + it->first, results); //this "it->second" refers to the Trie the iterator is operating on
            //it->first is the char here


        }
    }

    Trie traverse(string str){
        //Sam
        /*ARGS: str; string that we want to travel to in the trie
          RETURNS: Trie; the literal node that the str stops on

          This essentially crops a trie up to the input string.
          So if we had the string STO,
          traverse should travel along the S child to that node,
          then the T child of that node, then the O child
          */
        string next = str.substr(1,str.size()-1);
        cout << "we should reach here." << endl;
        for(map<char, Trie*>::iterator it = children.begin(); it != children.end(); it++){
            cout << "enter loop" << endl;
            if (str.size()==1){
                cout << "reached return of traverse" << endl;
                return *(it->second);
            }
            
            if (it->first == str[0]){
                cout << "traversing" << endl;
                it->second->traverse(next);
            }
        }
    }

    void getRackWords(const string& prefix, map<char, int>& rack, vector<string>& results){
        if (isEOW){
            results.push_back(prefix);
        }
        for(map<char, Trie*>::iterator it = children.begin(); it != children.end(); it++){
            if (
                (rack.find(it->first) != rack.end() && rack[it->first] > 0)||(rack.find('*') != rack.end() && rack['*'] > 0)){
                    if (rack.find(it->first) != rack.end()){
                        rack[it->first] -=1;
                        it->second->getRackWords(prefix + it->first, rack, results);
                        rack[it->first] +=1;
                    }
                    else {
                        rack['*'] -=1;
                        it->second->getRackWords(prefix + it->first, rack, results);
                        rack['*'] +=1;
                    }
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
Trie root;
bool init=false;
Trie getTrie() {
    if(init)return root;
    string temp = "";
    vector<string> results;
    string line;
    ifstream dict("dictionary.txt"); //opens it
    if (dict.is_open()){
        while (getline(dict, line)){
            root.insert(&*line.begin(), line.size());
        }
        dict.close();
    }
    init=true;
    return root;
    /*map<char, int> rack;
    rack['n'] = 1;
    rack['e'] = 2;
    rack['h'] = 1;
    rack['l'] = 1;
    rack['c']= 1;
    rack['*'] = 1;

    root.getRackWords(temp, rack, results);
    for(vector<string>::iterator it = results.begin(); it!= results.end(); it++){
            cout << *it << endl;
    }
    return 0;*/
}

//we also need a way of getting all possible letters from a given node
// we also need a way of getting the next node along the path of a letter.
