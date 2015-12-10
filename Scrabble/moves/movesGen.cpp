/* this will generate the moves
 *
 * 1. compute the anchor positions
 * 2. compute each cross-check
 * 3. compute all possible moves for rows/cols
 *   a. use LeftPart() and ExtendRight() from the paper
 * 4. Score all the moves
 * 5. Sort the moves
 * 6. return an array of moves
 * If this function becomes too monolithic, steps 4+5 can
 * be extracted to their own functions
 */
#include "utils.cpp"
using namespace std;

//Trie root;
multimap<string,Tile> legalMoves;

void LegalMove(string partialWord, Tile square){
    /*Sam
     * ARGS: string partialWord; the word that is a legal move.
     *       Tile square; the square on which the last letter should be placed.
     *       ^^Why is it the tile of the last letter? we need to know where to START and which way to go.
     * RETURNS:
     *      none, but it should somehow keep track of all the possible legal moves passed through it.
     *      I've defined multimap<string, tile> legalMoves outside the scope of this function.
     *      It is now global scope and should be accessible from movesGen.
     *      LegalMove should add a record to that map of strings->tiles {string:tile}
     -----
     -----
     -CAT-
     --#O-
     --*O-

     -----
     -*C--
     -#A--
     OOT--
     -----

     HASH IS AN ANCHOR FOR VERTICAL AND HORIZONTAL. MASS HYSTERIA.
     */
     legalMoves.insert(pair<string,Tile>(partialWord, square));
}

void ExtendRight(string partialWord, Trie n, Tile square, vector<Tile> rack, Board board){
    if(square.letter == 0){
        if(n.isEOW){ //if n is a terminal node
            LegalMove(partialWord,square); //I'm pretty sure the square will be the position of the last letter
        }
        for(map<char,Trie*>::iterator e=n.children.begin(); e!=n.children.end(); ++e){/*each edge e out of n*/
            bool LinRack = false; // l is in rack
            for(int i=0;i<rack.size();i++){
                LinRack = rack.at(i).letter==e->first;
            }
            bool xchecker = square.xchecks[((int)(e->first))-64];
            if(LinRack && xchecker){/*the letter l labeling edge E is in our rack AND l is in the xcheck set of square*/

                //remove a tile l from the rack
                Tile temp;
                for(int i=0;i<rack.size();i++){
                    if(rack.at(i).letter==e->first){
                        temp = rack.at(i);
                        rack.erase(rack.begin()+i);//remove rack[i] from the vector
                        break;
                    }
                }
                n=*(e->second);//n=node by following edge e

                //#next-square = the square to the right of square
                int x;
                vector<Tile> row;
                if(square.orient==1){
                    x = square.coords.at(0);
                    row = board.getRow(square.coords.at(1));
                } else {
                    x = square.coords.at(1);
                    row = board.getRow(square.coords.at(0));
                }
                if(x==15){
                    rack.push_back(temp);
                    return;//i dunno what to return, just return?
                }
                //If no words have been formed by this point then it won't matter
                Tile nextSquare = row.at(x+1);
                int tempOrient = nextSquare.orient;
                nextSquare.orient=square.orient;

                ExtendRight(partialWord+=(e->first),n,nextSquare,rack,board);
                nextSquare.orient = tempOrient;
                rack.push_back(temp); //put the tile l back into the rack


                /*
                 remove a tile l from the rack
                 n = the node reached by following edge E
                 next-square = the square to the right of square

                 ExtendRight(partialWord+l,N,next-square)
                 put the tile l back into the rack
                 */
            }
        }
    } else {
        // let l be the letter occupying square
        char l = square.letter;
        if(root.hasChild(l)){/*N has an edge labeled by l that leads to some node N*/
            int x;
            vector<Tile> row;
            if(square.orient==1){
                x = square.coords.at(0);
                row = board.getRow(square.coords.at(1));
            } else {
                x = square.coords.at(1);
                row = board.getRow(square.coords.at(0));
            }
            if(x==15) return;//i dunno what to return, just return?
            Tile nextSquare = row.at(x+1);
            int tempOrient = nextSquare.orient;
            nextSquare.orient=square.orient;
            ExtendRight(partialWord+=l,*(n.children[l]),nextSquare,rack,board);
            nextSquare.orient = tempOrient;
           /*next-square = tile to the right of square
            * ExtendRight(partialWord+l, N, next-square)
            */
        }
    }
}
void LeftPart(string partialWord, Trie n, int limit, vector<Tile> rack, Tile anchor, Board board){
    /* ARGS:
     *  partial word is the string to the left of the anchor
     *  Node N is in dawg after traversing up to the partial word
     *  limit is how many open, non-anchor squares there are to the left of the given anchor.
     *     for finding limit, we might want to add an isAnchor flag to the Tile struct. not sure.
     * RETURNS:
     *  This doesn't return anything. Everything is going to be done more-or-less inplace.
     *  Actual valid output moves are passed through LegalMove()
     */
    ExtendRight(partialWord, n, anchor, rack, board);
    if(limit>0){
        for(map<char,Trie*>::iterator e=n.children.begin(); e!=n.children.end(); ++e){/*each edge E out of n*/
            bool LinRack = false; // l is in rack
            for(int i=0;i<rack.size();i++){
                LinRack = rack.at(i).letter==e->first;
            }
            if(LinRack){/*the letter l labeling edge E is in our rack*/
                char l = e->first;
                //remove a tile l from the rack
                Tile temp;
                for(int i=0;i<rack.size();i++){
                    if(rack.at(i).letter==e->first){
                        temp = rack.at(i);
                        rack.erase(rack.begin()+i);//remove rack[i] from the vector
                        break;
                    }
                }
                n=*(e->second);//n=node by following edge e
                /*remove a tile labeled l from the rack
                 * let N be the node reached by following edge E
                 */
                LeftPart(partialWord+=l,n, limit-1, rack, anchor, board);
                rack.push_back(temp); //put the tile l back into the rack
                /*put tile back into rack*/
            }
        }
    }
}


vector<Board> findMoves(Tile anchor, Board board, vector<Tile> rack){
    // This returns a vector of boards because we don't know how many moves a specific anchor might yeild.
    /* orphaned, in progress.
     * ARGS: anchor; a Tile that we want to compute moves from.
     *       board; the board we are computing moves on.
     *       rack; the rack of tiles we are able to place onto the board.
     * RETURNS:
     *      a vector of Boards, length depends on how many moves are computed from the anchor
     *
     *      it should generate the vector of Boards based off of the records of LegalMove.
     */
    vector<Board> moves;
    int temp;
    if(anchor.orient==3){
        temp = anchor.orient;
        
        anchor.orient=1;
        vector<Board> horizMoves = findMoves(anchor, board, rack);
        moves.insert(moves.end(),horizMoves.begin(),horizMoves.end());

        anchor.orient=2;
        vector<Board> vertMoves = findMoves(anchor, board, rack);
        moves.insert(moves.end(),vertMoves.begin(),vertMoves.end());

        anchor.orient = temp;
        return moves;
    }
    string partialWord = findPartial(anchor, board);
    Trie n = root.traverse(partialWord);
    int limit = findLimit(anchor, board);
    LeftPart(partialWord, n, limit, rack, anchor, board);
    //after this point, LegalMove should have fully populated the legalMoves map above.
    //when converting from the map into a board, also keep track of the score and add it to
    for(multimap<string,Tile>::iterator it=legalMoves.begin(); it!=legalMoves.end(); ++it){
        Tile tile = it->second;
        string word = it->first;
        Board outBoard;
        outBoard.tiles = board.tiles;
        Tile lastTile = outBoard.getTile(tile.coords[0],tile.coords[1]);
        lastTile.letter = word[word.size()-1];

        if(tile.orient==1){
            int i=0;
            for(string::iterator str=(word.end()-1); str!=word.begin(); --str){
                Tile outTile = outBoard.getTile(tile.coords[0]-i,tile.coords[1]);
                outTile.letter = *str;
                //I should probably be keeping track of the score here as well;
                i++;
            }
        }
        if(tile.orient==2){
            int i=0;
            for(string::iterator str=(word.end()-1); str!=word.begin(); --str){
                Tile outTile = outBoard.getTile(tile.coords[0],tile.coords[1]-i);
                outTile.letter = *str;
                i++;
            }
        }

        outBoard.score = getScore(word,board,tile);
        moves.push_back(outBoard);
    }
    

    return moves;
}

vector<Board> findBest(vector<Board> moves){ //GNOME SORT FTW
    /* Sam
       returns the top 20 boards based on the boards find moves will return
    */
    vector<Board> best;
    for (int i = 0; i < moves.size()-1; i++){
        for (int j = 0; j < moves.size()-1; i++){
            if (moves.at(i).score > moves.at(i+1).score){
                Board temp = moves.at(i);
                moves.at(i) = moves.at(i+1);
                moves.at(i+1) = temp;
            }
        }
    }
    for (int i= 0; i <20; i++){
        best.push_back(moves.at(i));;
    }
    return best;
}


vector<Board> movesGen(Board board, vector<Tile> rack){
    //I believe this should call everything and return the best moves, which are instances of the board will a play on them
    //The trie is not global, I need to intialize it here.
    root = getTrie();
    //crossCheck(board);//after this step, we now know the valid "vertical" placements.
    vector<Tile> anchors = getAnchors(board);
    vector<Board> allMoves;
    for(int i=0;i<anchors.size();i++){
        vector<Board> moves = findMoves(anchors[i],board, rack);
        allMoves.insert(allMoves.end(),moves.begin(),moves.end());
    }
    allMoves = findBest(allMoves);
    return allMoves;
}
