#include <string>
#include <fstream>
#include <iostream>
#include <cstdlib> // for exit()
#include <array>
#include <map>
#include "weight.h"
using namespace std;

// this function scores a single word created on an existing board

//the word parameter must include all the letters of the word formed by the length of the placed letters
//the xaxis parameter provides the direction of that word: true if horizontal, false if vertical
int scoreword(char &board[][], string word, bool xaxis, int xstart, int, ystart){
    int length = word.length();
    char tile; // the boardgame representation of that spot
    int totalscore = 0; //ongoing return accumulator
    bool triple = false;
    bool doobel = false;
    int letterVal; // to contain the letter weight
    
    for (int i = 0; i < length; i++){
        if (xaxis){ tile = board[ystart][xstart+i];} //FIXME check that this works right
        else { tile = board[ystart+i][xstart]; } // and this
        letterVal = weight(word[i]);
        switch (tile){
            case '9':
                triple = true;
                totalscore += letterVal;
                break; 
            case '4':
                doobel = true;
                totalscore += letterVal;
                break; 
            case '3':
                totalscore += (3 * letterVal);
                break; 
            case '2':
                totalscore += (2 * letterVal);
                break; 
            default: 
                totalscore += letterVal;
        }
    }
    
    return totalscore;
}