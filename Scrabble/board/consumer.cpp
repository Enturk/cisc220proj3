#include <fstream>
#include <iostream>
#include <string>
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
    int row=0;
    while(inFile >> x) {
        int col=0;
        // This loops through each line of inFile and stores it
        // in variable x for each iteration.
        //
        //   note: the iterator line below looks scary. think of it as 
        //   "for each char it in x"
        for(string::iterator it = x.begin(); it!=x.end();++it){
            /*
             * TODO: create a tile for each character. This is the general scaffolding, it needs
             *  to be completed though.
             * keep track of column and row.
             * put that tile on the board. (board.getTile(col, row) = new Tile(it);)
             */
            Tile tile;
            if(0/* it is a letter */){//figure out how to test if a char is a letter.
                tile.letter = *it;
                tile.score = weight(*it); // nazim made a switching function for getting the int weights.
                                          // That will have to be included somewhere in here. Put it in ./lib/
                // we should probably also set bonus=0
            } else tile.letter = 0;
            if(0 /*it is a number */){//figure out how to test if a char is a number
                tile.bonus = (int)*it;//bonus is the int equivalent of the char. Not sure how to cast
                                      // a char to an int 
            }
            tile.coords = {col, row};//I don't know how to create an array on the fly.
            board.getTile(col, row) = tile;
            col++;
        }
        row++;
    }
    inFile.close();
    return board;
}

Tile* rackGen() {
    ifstream inFile;
    string x;

    Tile* tiles = new Tile[7];

    inFile.open("./board/board.txt");
    if(!inFile){
        cout << "File does not exist?" << endl;
        return NULL;
    }
    inFile >> x; //Store the rack line in variable x;
    
    int i=0;
    // for each char it in x 
    for(string::iterator it = x.begin(); it!=x.end();++it){
        // TODO: Make this work. Find how to do if it==(any ascii letter, upper or lower) 
        // create new tile, set its letter to it, set its score
        Tile tile;
        if(0/* it is a letter */){
            tile.letter = *it;
            tile.score = weight(*it);
            tile.coords = {-1}; // it's not on the board, coords shows that by {-1};
            //probably should set tile.bonus = 0;
        } else tile.letter = 0;
        i++;
    }
    inFile.close();
    return tiles;
}
