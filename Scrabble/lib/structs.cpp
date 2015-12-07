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
};
