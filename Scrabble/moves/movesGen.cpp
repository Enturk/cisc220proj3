/* this will generate the moves
 *
 * 1. compute each corss-check
 * 2. compute the anchor positions
 * 3. compute all possible moves for rows/cols
 *   a. use LeftPart() and ExtendRight() from the paper
 * 4. Score all the moves
 * 5. Sort the moves
 * 6. return an array of moves
 * If this function becomes too monolithic, steps 4+5 can
 * be extracted to their own functions
 */
#include <vector>
using namespace std;
void crossCheck(Board& board){
    /* This has to go through the board(rows and cols), look at the corresponding adjacent
     * tiles above and below(row+-1,col+-1) and see if the result for each letter is a word.
     * For the letters that do produce real words, check it off(set bit to 1) in tile.xchecks[index]
     * for each letter that does not produce a word in either the row or col, set the corresponding bit to 0
     *
     * ARGS: Board&, it has direct access to board.
     * RETURNS: none, it should edit the board tiles in place.
     */

    /* something like this, I don't know if this is the best way
     *
     * There is a challenge in finding contiguous chunks of letters.
     * Imagine we have a board like this:
     * 
     *   O
     * BOXES
     * U E
     * T*N
     * T
     *
     * TRANSPOSED:
     * 
     *  BUTT
     *  O *
     * OXEN
     *  E
     *  S
     * Placing an E at the star is legal, but if the cross check does not see that T+E+N creates a word,
     * it will mark E as invalid at the star position.
     * there should be some recursive element that accounts for contiguous chunks.
     *
     for(each row in board){
        for(each col in row){
            ostringstream str;
            board.getTile(row, col);
            str << board.getTile(row,col);
            str << board.getTile(row+1,col);
        }
    }*/
}

vector<Tile> getAnchors(Board board){
    /* Args: board; a Board with tiles on it. Tiles should have a completed xchecks vector associated w/ them.
     * RETURNS: vector<Tile> a list of all of the tiles that are anchors.
     * 
     * it might be best to add an "anchor" boolean for the tiles on the board.
     *
     * anchors are defined as the leftmost empty tiles adjacent to already placed tiles with non-trivial xchecks.
     * That is; they are the blank spots to the left of words already on the board(tile.letter==0)
     * and they have non-trivial crosschecks(there is at least one '1' in tile.xchecks
     */
    vector<Tile> anchors;
    return anchors;
}

string findPartial(Tile anchor, Board board){
    /* args: Tile anchor; the anchor from which we are computing
     *       Board board; the actual board object
     * RETURNS: the string of the prefix to the left of anchor, only from tiles that are already on the board
     */
}

Node traverseTrie(string partialWord){
    /* args: string partialWord. the string we want to travel up to
     * returns: a Node object, a piece of the trie with labeled edges and an acceptState boolean
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
void LeftPart(string partialWord, Node n, int limit){
    /* ARGS:
     *  partial word is the string to the left of the anchor
     *  Node N is in dawg after traversing up to the partial word
     *  limit is how many open, non-anchor squares there are to the left of the given anchor.
     *     for finding limit, we might want to add an isAnchor flag to the Tile struct. not sure.
     * RETURNS:
     *  This doesn't return anything. Everything is going to be done more-or-less inplace. 
     *  Actual valid output moves are passed through LegalMove()
     */
    ExtendRight(partialWord, n, anchor);
    if(limit>0){
        for(/*each edge E out of n*/){
            if(0/*the letter l labeling edge E*/){
                /*remove a tile labeled l from the rack
                 * let N be the node reached by following edge E
                 */
                LeftPart(partialWord+l,N, limit-1);
                /*put tile back into rack*/
            }
        }
    }
}
void ExtendRight(string partialWord, Node n, Tile square){
    if(0/*square is vacant*/){
        if(/*n is a terminal node*/0){
            LegalMove(partialWord,square)//I'm pretty sure the square will be the position of the last letter
        }
        for(/*each edge E out of n*/){
            if(/*the letter l labeling edge E is in our rack AND l is in the xcheck set of square*/){
                /*
                 remove a tile l from the rack
                 N = the node reached by following edge E
                 next-square = the square to the right of square
                 
                 ExtendRight(partialWord+l,N,next-square)
                 put the tile l back into the rack
                 */
            }
        }
    } else {
        /* let l be the letter occupying square
         */
         if(/*N has an edge labeled by l that leads to some node N*/){
            /*next-square = tile to the right of square
             * ExtendRight(partialWord+l, N, next-square
             */
         }
    }
}

void LegalMove(string partialWord, Tile square){
    /*
     * ARGS: string partialWord; the word that is a legal move.
     *       Tile square; the square on which the last letter should be placed.
     * RETURNS:
     *      none, but it should somehow keep track of all the possible legal moves passed through it.
     */
}

vector<Board> findMoves(Tile anchor, Board board, vector<Tile> rack){
    // This returns a vector of boards because we don't know how many movess a specific anchor might yeild.
    /* ARGS: anchor; a Tile that we want to compute moves from.
     *       board; the board we are computing moves on.
     *       rack; the rack of tiles we are able to place onto the board.
     * RETURNS:
     *      a vector of Boards, length depends on how many moves are computed from the anchor
     */
    vetor<Board> moves;
    string partialWord = findPartial(anchor, board, rack);
    Node n = traverseTrie(partialword);
    int limit = findLimit(anchor, board);
    LeftPart(partialWord, n, limit);
}

vector<Board> movesGen(Board board, vector<Tile> rack){
    crossCheck(board);//after this step, we now know the valid "vertical" placements.
    vector<Tile> anchors = getAnchors(board);
    vector<Board> allMoves;
    for(int i=0;i<anchors.size();i++){
        vector<board> moves = findMoves(anchors[i], board, rack);
        for(int j=0;i<moves.size();j++){
            allMoves.push_back(moves[j]);
        }
    }
    return allMoves;
}
