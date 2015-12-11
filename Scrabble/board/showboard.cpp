//#include <iostream> // includes need to be commented appropriately out after testing
#include "consumer.cpp"
#include <fstream>
#include <cstdlib> // for exit()
using namespace std;

// Nazooom
// compiles but untested
// this function simply prints the board and rack out from the saved text file or from the Board struct
int showboard(Board board){
    bool spaced = true; // FIXME set to false before turning in. True inserts spaces for the sake of legibility
    
    // switches to show other details of the board
    bool showAnchors = false; // not yet implemented
    bool showFirstXcheck = false; // not yet implemented
    bool loadBoard = false; // this skips old load code that I don't want to throw out

    if (loadBoard){
        // ifstream is used for reading files
        ifstream board("board.txt");
     
        // If we couldn't open the input file stream for reading
        if (!board) {  // Print an error and exit
            cout << "Uh oh, board.txt could not be opened for reading!" << endl;
            exit(1);
        }
    
        string strInput;
        // While there's still stuff left to read
        while (board) {        // read stuff from the file into a string and print it
            getline(board, strInput);
            if (spaced){ //FIXME the below prints out the last line twice
                for (int i = 0; i < 15; i++){
                    cout << strInput[i] << " ";
                }
                cout << endl;
            } else {
                cout << strInput << endl;
            }
        }
    }
    
    Tile temp;
    if (spaced) cout << "  1 2 3 4 5 6 7 8 9101112131415";
    else cout << "  123456789012345";
    for (int y = 0; y < 15; y++){
        cout << y+1 << " ";
        for (int x = 0; x < 15; x++){
            temp = board.getTile(y , x);
            if (temp.letter != '0') cout << temp.letter;
            else if (temp.bonus > 0) cout << temp.bonus;
            else cout << '-';
            if (spaced) cout << " ";
        }
        cout << endl;
    }
    
    return 0;
}

// comment the below out after testing is complete.
int main(){
    Board board = boardGen();
    showboard(board);
}
    