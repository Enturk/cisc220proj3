struct Tile {
    //This tile object is flexible enough to represent
    //  1. A wooden tile piece on our rack
    //  2. A wooden tile piece placed on the board
    //  3. A blank spot on the board
    char letter; //tile's letter (0 if no letter)
    int score; // letter's score (0 if above is zero)
    int bonus; // bonus on that tile (only if representing an empty spot on the board
    int* coords; // position of tile on board
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
};
