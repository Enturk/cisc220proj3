#include <iostream>
#include <vector>
#include <bitset>
#include <string.h>
#include "../lib/structs.cpp"
#include "../lib/trie.cpp"
#include "../board/consumer.cpp"
#include "utils.cpp"
using namespace std;

// Nazim
// will not compile 
string findPartial(Tile,Board);

void crossCheck(Tile& tile, Board& board){
    /* This has to go through the board(rows and cols), look at the corresponding adjacent
     * tiles above and below(row+-1,col+-1) and see if the result for each letter is a word.
     * For the letters that do produce real words, check it off(set bit to 1) in tile.xchecks[index]
     * for each letter that does not produce a word in either the row or col, set the corresponding bit to 0
     *
     * ARGS: Tile&, it has direct access to the tile it is checking.
            Board&, to modify it in place
     * RETURNS: none, it should edit the board tiles in place.
     */
    
    // STEP ONE check if tile is empty, if not skip tile
    // unnecessary because called by anchor
    /* int length = 1;
    char nextTile;
    int row = tile.coords.at(1)-length;
    while (row > 0){ // go up as long as can go up
        nextTile = board.getTile(tile.coords.at(0),tile.coords.at(1)-length).letter;
        if (nextTile != '0'){ // STEP TWO: check which adjacent tile has a letter
            partialword += nextTile;
        } else {break;} // stop moving up if we get to an empty tile
        length++;
        row--;
    }
    */
    // need to reverse partialword here if I then look it up in the for loop below.
    /*
    
    -----
    *CAT- This one is the only horizontal anchor, Tile.orient==1
    -----
    
    ---
    *C-
    *A- These are going to be considered vertical, anchor.orient==2
    0T-
    ---
    
    I just set up the anchors. Oh, it doesn't matter. 
    0 is marked as a specific anchor above.
    findPartial(0,board) will give you "T"
    
    Easier to debug one implementation, not two. That being said, I'll clean up other code and let you finish here.
    but pls don't rewrite a partial word finding function
    
    Nazim says: I don't think partial word will find words that go across the anchor tile
    ... or at least not in this implementation. Riley pushed for this, but I'm not sure how to implement that.
    
    what nazim says is right. partial word will get whatever is to the left in the contiguous row.
    but what you want to find is what is above. simple fix is to flip the orientation so that findPartial thinks it should go upwards.
    tile orientations are either 1 for horizontal, or 2 for vertical. also 3 for both. findPartial doesn't handle the orient=3 case.
    
    set orientation like
    tile.orient=whatever.
    whatever above should be the opposite(1 is 2, and 2 is 1) of the original.
    */
    // 
    string partialword = findPartial(tile, board);
    int wordLength = partialword.length()+1;
    Trie trie = getTrie();
    // string bitContainer = "00000000000000000000000000"; // container  (unused)
    string word;
    string alphabet =     "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    for (int i = 0; i < 26; i++){
        word = partialword + alphabet[i];
        
        char *y = new char[word.length()+1];
        strcpy(y, word.c_str());
        tile.xchecks[i] = trie.hasWord(y, wordLength); // I'm a genius. That's Nazim. He really is. 
        delete[] y;
    }

    
    /*
    so moves can only be done in the relative horizontal
    -***-  -***-
    -CAT-  -COG- 
    -O**-  -A**-
    -G---  -T---
    -*---  -*---
    These two boards are synonymous. As such, the plays only ever happen in one
    dimension. That is to say, a vertical move is really just a rotated horizontal move
    
    Since moves are only ever horizontal, the vertical words are only ever going to change by
    a maximum of one letter. COLs can only ever have one letter added to them. 
    
    Well, that's why we just do both orientations. So the left is is just the right.
    we do cross checks in consideration of the rows as well as the colums.
    
    We are going to do a crosscheck on each position marked with a star. Notice how
    all possible situations are covered by both representations.
    If I pot So
    
    basically we are just assuming that each "word" in each row/column is going to get
    incremented by one in either direction.
    
    Okay, well notice how I put SO "vertically" at the end of COGS. Well that Position
    had a crosscheck computed for it. the star at the end of COG in the first diagram.
    
    Crosschecking is going to go to that tile, and put every possible letter there.
    
    For every letter that creates a word from the stuff before it, Check that off in a bitvector
    ABCDEFGHIJKLMNOPQRSTUVWXYZ
    00000000000000000010000000
    COG+S made COGS, that is a valid word, we can put an S there. So then, when that
    anchor square is considered, we already know what is allowable.
    
    So, in some configurations, it might have to check a couple of tiles away. EG:
    I have an example below considereing the TEN
    
    I saw that, but both of those are adjacent. In my example the starred tiles have to check two tiles away.
    And so on. So what we need is a checkword function buried in xcheck.
    --------
    -WORD---
    -WORD---
    -****---
    well I just see this as a recursive problem. Or wait, I think check partial is going to 
    do something just like this.
    You might be able to call check partial on the col/row previous to the xcheck spot.
    well no, i mean it's going to do the same thing where it digests and returns 
    contiguous groups of tiles that form parts of words.
    
    That wouldn't be an empty tile, so the recursion would stop at step one.
    
    Follow me at the bottom.
    
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
     * there should be some recursive element that accounts for these contiguous chunks.
     *
     for(each row in board){
        for(each col in row){
            ostringstream str;
            board.getTile(row, col);
            str << board.getTile(row,col);
            str << board.getTile(row+1,col); //the next row down 
            Yes, I saw that, but down or across doesn't matter if we don't have an orientation yet
            this function is called BEFORE any anchor checking, and therefore before we have an orientation   
            no i do see what you're saying. the orientation is there, like the board is still
            interpreted by us (and in the code with the getTile function) in two dimensions.
            but like, you can just go to a tile and see adjacency and then start working on 
            xchecking depending on the direction of adjacency
            
            but then we run into an issue where I have
            ----
            cat!
            -*--
            a is adjaacent to c, we should crosscheck to the right of a.
            and then it computes a xcheck for the tile t, which already has a tile
            What I'm suggesting below skips that at step one. We'd start at *, for example.
            Then we'd move upwards to see if there's a letter. So, we'd find that there is one.
            Then we'd look up further, to see if there's another letter, and stop there because there isn't.
            On the other hand, if we checked 
        }
    }*/

    
};


int main(){
    
    cout << "censored of fire"<<endl;
}