#include <iostream>
#include <sstream>
#include <bitset>
//#include weights.cpp
using namespace std;

struct Tile {
    //This tile object is flexible enough to represent
    //  1. A wooden tile piece on our rack
    //  2. A wooden tile piece placed on the board
    //  3. A blank spot on the board
    char letter; //tile's letter (0 if no letter)
    int weight; // letter's score (0 if above is zero)
    int bonus; // bonus on that tile (only if representing an empty spot on the board
    vector<int> coords; // position of tile on board
    bool anchor;
    int orient;
    bitset<26> xchecks;
    // coords is {0}(one index array of -1) if tile
    // is not on the board.
    Tile(){};
    Tile(char l, int W, int b, vector<int> c){
      letter= l;
      weight = W;
      bonus = b;
      coords = c;
      anchor = false;
      orient = 0;
      xchecks = xchecks.set();
    }
};

// Sam
struct Board {
    // the board has a one dimensional array of Tiles
    vector<Tile> tiles;
    int score; //boards are only scored if we have put a move onto it
   
    Tile getTile(int col, int row){
        //the index of a tile with coordinates of (x,y) in the 2D array is (15*x)+y.
        return tiles[15*row + col];
    }

    vector<Tile> getRow(int row){
        /* ARGS: row; integer to represent the row
         * RETURNS: an vector of tiles in that row.
         */
         vector<Tile> r;
         for (int i = 0; i < 15; i++){
           r.push_back(tiles.at(15*row + i)); //adds each tile in that row to the vector
         }
         return r;
    }
    vector<Tile> getCol(int col){
        /* ARGS: col; integer to represent a col.
         * RETURNS: a vector of tiles in that col
         */
         vector<Tile> c;
         for (int i= 0; i < 15; i++){
           c.push_back(tiles.at(15*i + col));
         }
         return c;
    }

    ostream& operator<<(const Board& board){
        /* This may or may not be working
         * ARGS: const Board& board; an input board
         * RETURNS: ostream; an output stream object for <<'ing into cout.
         *
         * if I do cout << board;, this should return an output stream object that has the board in it
         *
         * This is a way of printing the board
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
