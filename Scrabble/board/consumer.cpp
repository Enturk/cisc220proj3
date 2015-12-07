#include <fstream>
#include <iostream>
#include <string>
#include <vector>
//#include weights.cpp          not the right way to include these... not sure what path it should be
//#include ./lib/structs.cpp
using namespace std;

/* Input data consumer functions
 *
 * Includes functions for reading in and creating the
 * board object that we will be reading from. Crucial
 * that it does this in a way that is inline with the
 * expectations of the rest of the functions.
 */

Board boardGen() {
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
    board.tiles = new Tile[15*15];

    if(!inFile){
        cout << "File does not exist?" << endl;
        return *(new Board());
    }

    inFile >> x; //skip the first line(the rack)
    int countX = 0;
    while(inFile >> x) {
       int countY = 0;
        // This loops through each line of inFile and stores it
        // in variable x for each iteration.
        //
        //   note: the iterator line below looks scary. think of it as
        //   "for each char it in x"
        for(string::iterator it = x.begin(); it!=x.end();++it){
          if (*it == '-'){
            board.tiles.push_back(new Tile('',0,0, {countX,countY}));
          }
          if (isalpha(*it)){
            board.tiles.push_back(new Tile(*it, 0, weight(*it), {countX,countY}));
          }
          if(isdigit(*it)){
            board.tiles.push_back(new Tile('', *it, 0, {countX,countY}));
          }
        countY++;
        }
        countX++;
    }
    inFile.close();
    return board;
}

vector<Tile> rackGen() {
    ifstream inFile;
    string x;

    Tile* tiles = new Tile[7];

    inFile.open("./board/board.txt");
    if(!inFile){
        cout << "File does not exist?" << endl;
        return 0;
    }
    inFile >> x; //Store the rack line in variable x;
    vector<Tile> rwords(7); // array the tiles that the rack letters make
    // for each char it in x
    for(string::iterator it = x.begin(); it!=x.end();++it){
        rwords.at(*it) = new Tile(*it, weight(*it), 0, {-1}); // initializes tile with no bonus and default coord of -1
    }
    inFile.close();
    return tiles;
}
