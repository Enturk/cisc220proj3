#include<iostream>
#include<sstream>
#include<bitset>
using namespace std;
struct Tile {
    //This tile object is flexible enough to represent
    //  1. A wooden tile piece on our rack
    //  2. A wooden tile piece placed on the board
    //  3. A blank spot on the board
    char letter; //tile's letter (0 if no letter)
    int score; // letter's score (0 if above is zero)
    int bonus; // bonus on that tile (only if representing an empty spot on the board
    int* coords; // position of tile on board
    bitset<26> xchecks;
    // coords is {0}(one index array of -1) if tile
    // is not on the board.
};

struct Board {
    // the board has a one dimensional array of Tiles
    Tile* tiles;
    /* Functions to be added:
     * Tile& getTile(int x, int y):
     *      this should do a mathematical operation to 
     *      take an x and y and return the corresponding
     *      tile from the tiles array.
     *      Make it return the reference, so tiles can be
     *      set by board.getTile(0,0) = myTile;
     *
     * operator<<() Overload;
     *      Overload the << operator to print a board
     *      exactly in the format of the input board
     *      (see board/board.txt for an example)
     */
    Tile getTile(int col, int row){
        /* ARGS: 
         *      col, row: integers that represent the x,y coordinate on the board
         * RETURNS:
         *      Tile: The tile at the specified col, row.
         */
        return tiles[0/*some flattening mathematical function.
                       that is; it should always return a single unique number when I give it a col and a row*/];
    }
    Tile* getRow(int row){
        /* ARGS: row; integer to represent the row
         * RETURNS: an array of tiles in that row.
         */
    }
    Tile* getCol(int col){
        /* ARGS: col; integer to represent a col.
         * RETURNS: an array of tiles in that col
         */
    }

    ostream& operator<<(const Board& board){
        /* if I do cout << board;, this should return an output stream object that has the board in it
         */
        ostringstream os;//this throws warnings. I probably did something wrong;
        for(int i=0;i<15;i++){
            for(int j=0;j<15;j++){
                Tile tile = getTile(j,i);
                if(tile.letter==0)os << '-';
                else os << tile.letter;
            }
        }
        return os;
    }
};
