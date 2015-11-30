#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib> // for exit()
using namespace std;

*char[][] readboard(&char[][] game){
    // ifstream is used for reading files
    // We'll read from a file called Sample.dat
    ifstream board("board.txt");
 
    // If we couldn't open the input file stream for reading
    if (!board)
    {
        // Print an error and exit
        cout << "Uh oh, board.txt could not be opened for reading!" << endl;
        exit(1);
    }

    string strInput;
    getline(board, strInput);

    // While there's still stuff left to read
    for (int j = 0; j < 15; j++) {     // read stuff from the file into the 2D char array
        getline(board, strInput);
        for (int i = 0; i < 15; i++){
            game[j][i] = strInput[i];
        }
    }
        
    return game;
}

// add testing here!