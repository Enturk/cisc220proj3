#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "../lib/weight.cpp"
using namespace std;

/* Input data consumer functions
 *
 * Includes functions for reading in and creating the
 * board object that we will be reading from. Crucial
 * that it does this in a way that is inline with the
 * expectations of the rest of the functions.
 */

Board boardGen() {
    //the girl
    /* Returns a Board object
     * This board is expected to be comprised of a
     * one-dimensional array of tiles (board.tiles)
     *
     * About representing a 2D board in 1D.
     * Board should have getter/setter functions
     * for its tiles array that uses a standardized
     * mathematical operation to "flatten" and "deflatten"
     * the board. It should be abstracted in such a way
     * that you can call board.set(0,0) = tile;
     *
     * more on that in the board struct.
     */
    ifstream inFile;
    string x;
    inFile.open("./board/board.txt");

    Board board;
    board.tiles = vector<Tile>();

    if(!inFile){
        cout << "File does not exist?" << endl;
        return *(new Board());
    }

    inFile >> x; //skip the first line(the rack)
    int countY = 0;
    while(inFile >> x) {
       int countX = 0;
        // This loops through each line of inFile and stores it
        // in variable x for each iteration.

        for(string::iterator it = x.begin(); it!=x.end();++it){
          if (*it == '-'){
            vector<int> coords;
            coords.push_back(countX);
            coords.push_back(countY);
            board.tiles.push_back(*(new Tile(0,0,0, coords)));
          }
          if (isalpha(*it)){
            vector<int> coords;
            coords.push_back(countX);
            coords.push_back(countY);
            board.tiles.push_back(*(new Tile(*it, 0, weight(*it), coords)));
          }
          if(isdigit(*it)){
            vector<int> coords;
            coords.push_back(countX);
            coords.push_back(countY);
            board.tiles.push_back(*(new Tile(0, *it, 0, coords)));
          }
          countX++;
        }
        countY++;
    }
    inFile.close();
    return board;
}

vector<Tile> rackGen() {
    //the girl
    ifstream inFile;
    string x;

    vector<Tile> tiles;

    inFile.open("./board/board.txt");
    if(!inFile){
        cout << "File does not exist?" << endl;
        return tiles;
    }
    inFile >> x; //Store the rack line in variable x;
    // for each char it in x
    for(string::iterator it = x.begin(); it!=x.end();++it){
        vector<int> coords;
        coords.push_back(-1);
        tiles.push_back(*(new Tile(*it, weight(*it), 0, coords))); // initializes tile with no bonus and default coord of -1
    }
    inFile.close();
    return tiles;
}
