#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <iostream>
#include <cstdlib> // for exit()
using namespace std;


int main(){
    bool updated = true;
    char[14][14] board;
    string rack;
    
    string inp;
    cout << "Is board.txt the updated board?" << endl;
    cin >> inp;
    if (inp[0] != y && inp[0] != Y){updated = false;}
    else {   
        // imports board to array
        ifstream board("board.txt");
        if (!board) {
            // Print an error and exit
            cout << "Uh oh, board.txt could not be opened for reading!" << endl;
            exit(1);
        }
        getline(board, rack);
        readboard(*board);
    } 
    
    /* TODO:
    if board isn't updated, update the board with the python script - don't know if possible
    find the top scoring words based on the rack and letters available on the board
    factor the score multipliers based on position to give the highest scoring play
    */
    
    return 0;
}
