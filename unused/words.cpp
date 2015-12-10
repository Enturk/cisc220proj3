#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <cstdlib> // for exit()
using namespace std;

// incomplete

// this struct is to describe words that COULD be placed on the board
// not sure this is the best way to deal with possible words, but it feels like it
struct Words {
    string word;
    bool xaxis;
    int xstart;
    int ystart;
    
    Words(string word, bool xaxis, int xstart, int ystart){
        this->word = word;
        this->xaxis = xaxis;
        this->xstart = xstart;
        this->ystart = ystart;
    }
    
    ~Words(){
        //FIXME what goes in here?
    }
};

// testing
int main() {
    Words* bird = new Words("bird", true, 5, 7);
    cout << "Word should be 'bird' and is " << bird->word << endl;
    cout << "Xaxis should be true and is " << bird->xaxis << endl;
    cout << "X and y should be 5 and 7, and are " << bird->xstart << " and " << bird->ystart << endl;
    
    return 0;
}