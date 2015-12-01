#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib> // for exit()
using namespace std;

// this function simply prints the board and rack out from the saved text file

int showboard(){
    // ifstream is used for reading files
    ifstream board("board.txt");
 
    // If we couldn't open the input file stream for reading
    if (!board)
    {
        // Print an error and exit
        cout << "Uh oh, board.txt could not be opened for reading!" << endl;
        exit(1);
    }

    string strInput;
    bool spaced = true; // FIXME set to false before turning in. True inserts spaces for the sake of legibility
    
    // While there's still stuff left to read
    while (board)
    {        // read stuff from the file into a string and print it
        getline(board, strInput);
        if (spaced){ //FIXME prints out the last line twice
            for (int i = 0; i < 15; i++){
                cout << strInput[i] << " ";
            }
            cout << endl;
        }
        else {
            cout << strInput << endl;
        }
    }
        
    return 0;
}

int main(){
    //used only for testing
    showboard();
}
    