#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <iostream>
#include <cstdlib> // for exit()
#include "readboard.h"
using namespace std;


int main(){
    bool updated = true;
    char* board; // AAAAAAAH - POINTERS - AAAAAAAAGH!
    string rack;
    
    string inp;
    cout << "Is board.txt the updated board?" << endl;
    cin >> inp;
    if (inp[0] != 'y' && inp[0] != 'Y'){updated = false;}
    else {   
        // imports board to array
        ifstream board("board.txt");
        if (!board) {
            // Print an error and exit
            cout << "Uh oh, board.txt could not be opened for reading!" << endl;
            exit(1);
        }
        getline(board, rack);
        //board = readboard(); // not sure if this will work
    } 
    
    // TODO: if board isn't updated, update the board with the python script - don't know if possible
    
    //  find all the words based on the rack and letters available on the board
    
    
    // give the highest scoring play
    
    return 0;
}
