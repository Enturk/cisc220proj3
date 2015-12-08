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
     *
     * Anchors should mark the tile as such. Tile.anchor = true;
     *   Anchors should also be denoted as a row or a col anchor.
            do this by setting tile.orient = 0, or 1, 2;
            tiles should default to 0.
            1 means horizontal. 2 means vertical.
            I need to know this to know which direction to compute the partialWord.
            added int orient to Tile struct
     */
    vector<Tile> anchors;
    vector<Tile> finalAnchs;
    for (int i = 0; i < 15; i++){
        for (int j = 0; j < 14; j++){ // has to go only to 14 because we do j+1 
            Tile t = board.getTile(i,j);
            Tile nextTo = board.getTile(i, j+1);
            if (t.letter == '' && isalpha(nextTo.letter)){ //checks if the tile is empty and the tile next to it has a letter
                anchors.push_back(board.tiles.at(i));
            }
        }
    }
    
    for (int i = 0; i < anchors.size(); i++){ // runs xcheck on all the anchors
        crossCheck(anchors.at(i));
        if (anchors.at(i).xchecks !=){
            finalAnchs.push_back(anchors.at(i));
        }
    }
    for (int i = 0; finalAnchs.size(); i++){
        finalAnchs.at(i).anchor = true;
    }
    return anchors;
}

string findPartial(Tile anchor, Board board){
    /* I think this should be done on rows of tiles, not the entire board. this
     * way we understand the orientation we are working with.
     * In this case, row is a generic list of Tiles, could be either vertical
     * or horizontal
     * args: Tile anchor; the anchor from which we are computing
     *       Board board; the actual board object
     * RETURNS: the string of the prefix to the left(or above) of anchor, only from tiles that are already on the board
     * I'm going to assume the input is the row
     */
     
     int dir = anchor.orient;
    
     //if dir is horiz and x=0 or dir is vert and y is zero, return empty string.
     if((dir==1 && x==0) || (dir==2 && y==0)) return "";
     
     vector<Tile> row; //the 'row' we are looking at
     int x; //the pos of the anchor
     if(dir==1){
         x = anchor.coords[1];
         row = board.getRow(x);
     }
     else{
         x = anchor.coords[0];
         row = board.getCol(x);
     } 
     int i=x;
     string out;
     for(i;row[i-1].letter!=''&&i>0;i--);//
     for(i;i<x;i++){
        out.append(row[i].letter);
     }
     return out;
}

int findLimit(Tile anchor, Board board){
    /* args: Tile anchor, the anchor we want to find the left limit of.
     *       Board board, the board to analyze
     * returns: the number of non-anchor tiles to the left of anchor.
     */
    int limit = 0;
    //find the coordinate of the anchor on the board
    int xcoord = anchor.coords.at(0);
    int ycoord = anchor.coords.at(1);
    //check from the anchor to the beginning of the row to add to limit count
    //if it reaches another anchor limit is stopped
    for (int i = ycoord; i > 0; i--){
        //stops the limit count if it hits another anchor
        if (board.tiles.at(xcoord*15 + i).anchor){
            return limit;
        }
        //increases the limit count for each non-anchor tile left of it that it reaches
        else{
            limit++;
        }
    }
    return limit;
}