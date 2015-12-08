vector<Tile> getAnchors(Board board){
    /* Args: board; a Board with tiles on it. Tiles should have a completed xchecks vector associated w/ them.
     * RETURNS: vector<Tile> a list of all of the tiles that are anchors.
     * 
     * it might be best to add an "anchor" boolean for the tiles on the board.
     *
     * anchors are defined as the leftmost empty tiles adjacent to already placed tiles with non-trivial xchecks.
     * That is; they are the blank spots to the left of words already on the board(tile.letter==0)
     * and they have non-trivial crosschecks(there is at least one '1' in tile.xchecks
     *
     * once we decide a tile is an anchor, run xcheck on it.
     */
    vector<Tile> anchors;
    return anchors;
}

string findPartial(Tile anchor, Board board){
    /* I think this should be done on rows of tiles, not the entire board. this
     * way we understand the orientation we are working with.
     * args: Tile anchor; the anchor from which we are computing
     *       Board board; the actual board object
     * RETURNS: the string of the prefix to the left(or above) of anchor, only from tiles that are already on the board
     */
}
int findLimit(Tile anchor, Board board){
    /* args: Tile anchor, the anchor we want to find the left limit of.
     *       Board board, the board to analyze
     * returns: the number of non-anchor tiles to the left of anchor.
     *
     * NOTE: I think we might need an anchor bool for Tiles on the board.
     */
}