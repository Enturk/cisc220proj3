#include <string>
#include <fstream>
#include <iostream>
#include <cstdlib> // for exit()
#include <array>
#include <map>
#include "weight.h"
using namespace std;


//the word parameter must include all the letters of the word formed by the length of the placed letters
//the xaxis parameter provides the direction of that word: true if horizontal, false if vertical
int scoreplay(string word, bool xaxis, int xstart, int, ystart){
    int length = word[].size();
    char tile; // the boardgame representation of that spot
    int totalscore = 0; //ongoing return accumulator
    int wordscore = 0; //score accumulator for each new word created by the new letters on board
    
   
}