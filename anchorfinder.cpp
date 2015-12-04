#include "readboard.h" // for testing
using namespace std;

// function that returns a 2D array of booleans representing the vacant spots
// adjacent to an existing letter
bool anchorfinder(char& board){ //FIXME this parameter... pointers, argh!
    bool anchor[14][14]; //or one array of 225 elements if Riley is right
    for (int i = 0; i < 15; i++){
        for (int j = 0; j < 15; i++){
            anchor[i][j] = false; // set board spaces to unavailable by default
            
            if (board[i][j] == '9' || // check that the tile in question is blank
                board[i][j] == '4' || // TODO must move these to a method called isBlank returning a bool
                board[i][j] == '3' ||
                board[i][j] == '2' ||
                board[i][j] == '-'){
                    if (i > 0){ // check that we're lower than the top row
                        if (board[i-1][j] != '9' && // set anchor to true if tile above is NOT blank
                            board[i-1][j] != '4' &&
                            board[i-1][j] != '3' &&
                            board[i-1][j] != '2' &&
                            board[i-1][j] != '-'){
                                anchor[i][j] = true;
                            }
                    } 
                    
                    if (i < 14){ // check that we're higher than the bottom row
                        if (board[i+1][j] != '9' && // set anchor to true if tile above is NOT blank
                            board[i+1][j] != '4' &&
                            board[i+1][j] != '3' &&
                            board[i+1][j] != '2' &&
                            board[i+1][j] != '-'){
                                anchor[i][j] = true;
                            }
                    }
                    
                    if (j > 0){ // check that we're right of the left column
                        if (board[i][j-1] != '9' && // set anchor to true if tile above is NOT blank
                            board[i][j-1] != '4' &&
                            board[i][j-1] != '3' &&
                            board[i][j-1] != '2' &&
                            board[i][j-1] != '-'){
                                anchor[i][j] = true;
                            }
                    }
                    if (j < 14){ // check that we're left of the right column
                        if (board[i][j+1] != '9' && // set anchor to true if tile above is NOT blank
                            board[i][j+1] != '4' &&
                            board[i][j+1] != '3' &&
                            board[i][j+1] != '2' &&
                            board[i][j+1] != '-'){
                                anchor[i][j] = true;
                            }
                    }

                }
        }
    }
    
    return anchor; 
}

// for testing: comment this main out when working off of main, along with the include readboard above
int main() {
    char* board = readboard();
    bool anchor[14][14] = anchorfinder(board);
    
    return 0;
}