#include <iostream>
#include <string.h>
#include <vector>
#include <bitset>
#include <map>
#include <fstream>
#include "../lib/structs.cpp"
#include "../lib/trie.cpp"

/*
#ifndef STRUCTS_I
#define STRUCTS_I
#include "../lib/structs.cpp"
#endif
#ifndef XCHECK_I
#define XCHECK_I
#include "../moves/xcheck.cpp"
#endif
*/
using namespace std;

string findPartial(Tile anchor, Board board){
    /* -rlyshw. this is finished. needs testing
    I think this should be done on rows of tiles, not the entire board. this
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
     if((dir==1 && anchor.coords.at(0)==0) || (dir==2 && anchor.coords.at(1)==0)) return "";

     vector<Tile> row; //the 'row' we are looking at
     int x; //the pos of the anchor
     if(dir==1){ //we going horizontally
         x = anchor.coords.at(0);
         row = board.getRow(anchor.coords.at(1));
     }
     else{ // we going vertically
         x = anchor.coords.at(1);
         row = board.getCol(anchor.coords.at(0));
     }
     int i=x;
     string out;
     for(i;row.at(i-1).letter!=0&&i>0;i--);//
     for(i;i<x;i++){
        out.append(string(1,row.at(i).letter));
     }
     return out;
}

void crossCheck(Tile& tile, Board& board){
    // Nazim
    /* Need to deal with orientation and other side of the tile
    tile.orient is 1 if just horizontal, 2 if just vertical, 3 if both
    
    Scenario 1 passes orient 1 (taken care of automatically)
    ---
    -C-
    -A-
    -T*
    ---
    
    Scenario 2 passes orient 2 (taken care of automatically)
    -----
    -CAT-
    -*---
    
    Scenario 3 passes orient 3 
    -----
    -CAR-
    -A*--
    -T---
    -----
    after running partial word horizontally (if necessary) => result 1
    do get col, run findPartial on the right tile => result 2
    loop tile.xchecks to result 1 AND result 2
    */
    
  string partialword = findPartial(tile, board);
  int wordLength = partialword.length()+1;
  Trie trie = getTrie();
  string word;
  string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  bool swingBothWays = false;
  if (tile.orient == 3){ // scenario 3: first runs in orient 1, then below in orient 2
      swingBothWays = true; 
      tile.orient = 1;
      Tile temp = tile;
      crossCheck(temp, board);
      bitset<26> xcheck1 = temp.xchecks;
      temp.orient = 2;
      crossCheck(temp, board);
      bitset<26> xcheck2 = temp.xchecks;
      tile.xchecks = (xcheck1 & xcheck2);
/*        for (int i = 0; i < 26; i++){
          word = partialword + alphabet[i];
          char *y = new char[word.length()+1];
          strcpy(y, word.c_str());
          temp.xchecks[i] = trie.hasWord(y, wordLength); // I'm a genius. That's Nazim. He really is.
          delete[] y;
        }
    tile.orient = 2*/
  } else {
  for (int i = 0; i < 26; i++){
      word = partialword + alphabet[i];
      char *y = new char[word.length()+1];
      strcpy(y, word.c_str());
      tile.xchecks[i] = trie.hasWord(y, wordLength); // I'm a genius. That's Nazim. He really is.
      delete[] y;
    } 
  }
    /*if (swingBothWays){
      tile.orient = 3;
        for (int i = 0; i < 26; i++){
            tile.xchecks[i] = temp.xchecks[i] && tile.xchecks[i]; //Still more genius.
        }
    }*/
}

vector<Tile> getAnchors(Board board){
    //Sam-complete, needs testing
    /* Args: board; a Board with tiles on it. Tiles should have a completed xchecks vector associated w/ them.
     * RETURNS: vector<Tile> a list of all of the tiles that are anchors.
     * anchors are defined as the leftmost empty tiles adjacent to already placed tiles with non-trivial xchecks.
     * That is; they are the blank spots to the left of words already on the board(tile.letter==0)
     * and they have non-trivial crosschecks(there is at least one '1' in tile.xchecks
     * once we decide a tile is an anchor, run xcheck on it.
     * Anchors should mark the tile as such. Tile.anchor = true;
     *   Anchors should also be denoted as a row or a col anchor.
            do this by setting tile.orient = 0, or 1, 2, 3;
            tiles should default to 0.
            1 means horizontal. 2 means vertical.
            I need to know this to know which direction to compute the partialWord.
            added int orient to Tile struct
     */
    vector<Tile> anchors;
    vector<Tile> finalAnchs;
    for (int i = 0; i< 14; i++){ //rows
        for (int j = 0; j < 14; j++){ // has to go only to 14 because we do j+1 //cols
            Tile t = board.getTile(i,j);
            Tile nextTo = board.getTile(i+1, j); //to its left
            Tile below = board.getTile(i, j+1);
            if (t.letter == 0 && isalpha(nextTo.letter)){ //checks if the tile is empty and the tile next to it has a letter
                anchors.push_back(board.tiles.at(i));
                board.tiles.at(i).orient = 1; //horizontal (the way the board normally looks)
            }
            if (t.letter == 0 && isalpha(below.letter)){
                anchors.push_back(board.tiles.at(i));
                board.tiles.at(i).orient = 2; //vertically
            }
            if (t.letter == 0 && isalpha(nextTo.letter) && isalpha(below.letter)){
                anchors.push_back(board.tiles.at(i));
                board.tiles.at(i).orient = 3; //vertically AND horizontally. special.
            }
        }
    }
    //cross checks eberything that is adjacent to a filled tile.
    for (int i =1; i <14; i++){
        vector<Tile> row = board.getRow(i);
        vector<Tile> col = board.getCol(i);
        if (row.at(i).letter == 0 && (isalpha(row.at(i+1).letter) || isalpha(row.at(i-1).letter))){
            crossCheck(row.at(i), board);
            row.at(i).orient = 1;
        }
        if (col.at(i).letter == 0 && (isalpha(col.at(i+1).letter) || isalpha(col.at(i-1).letter))){
            crossCheck(row.at(i), board);
            row.at(i).orient =2;
        }
        if (col.at(i).letter == 0 && (isalpha(col.at(i+1).letter) || isalpha(col.at(i-1).letter) && row.at(i).letter == 0 && (isalpha(row.at(i+1).letter) || isalpha(row.at(i-1).letter)))){
            crossCheck(row.at(i), board);
            row.at(i).orient = 3;
        }
    }
    for (int i = 0; i < anchors.size(); i++){ // runs xcheck on all the anchors
        if ((anchors.at(i).xchecks).count() !=0){ //checks to make sure the bitset isn't trivial (all 0s)
            finalAnchs.push_back(anchors.at(i));
        }
    }
    for (int i = 0; finalAnchs.size(); i++){
        finalAnchs.at(i).anchor = true;
    }
    return finalAnchs;
}



int findLimit(Tile anchor, Board board){
    //Sam--complete, needs testing
    /* args: Tile anchor, the anchor we want to find the left limit of.
     *       Board board, the board to analyze
     * returns: the number of non-anchor tiles to the left of anchor.
     */
    int limit = 0;
    int xcoord;
    int ycoord;
    //find the coordinate of the anchor on the board
    if (anchor.orient ==1){ //computes the limit horizontally
        xcoord = anchor.coords.at(0);
        ycoord = anchor.coords.at(1);
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
    }
    else if (anchor.orient ==2){ //checks the limit vertically if the anchor is orient 2
        xcoord = anchor.coords.at(0);
        ycoord = anchor.coords.at(1);
        for (int i = xcoord; i > 0; i--){
            //stops the limit count if it hits another anchor
            if (board.tiles.at(i*15 + ycoord).anchor){
                return limit;
            }
            //increases the limit count for each non-anchor tile left of it that it reaches
            else{
                limit++;
            }
        }
    }
    return limit;
}

int getScore(string partialWord, Board board, Tile endTile){
        //Josh
        /* ARGS: partialWord; legal partial word combination formed from rack tiles
         *       board; current board
         *       endTile; last tile of the word in question
         *RETURNS: The score of the playable word
         */
        Board tempBoard = board;
        int x = endTile.coords.at(0);
        int y = endTile.coords.at(1);
        int score = 0;
        int doubleWord = 0;
        int tripleWord = 0;
        int length = partialWord.length();

        //Word is horizontally oriented
        if (endTile.orient == 1){
            //Places tiles onto a temporary side board in order to compute values of all
            //letters in the board in place
            for(int i = length; i >= 0; i--){
                tempBoard.tiles.at(15*y + x).letter = partialWord.at(i);
                x -= 1; 
            }
            //Computes the score of each letter including double and triple letter bonuses
            //Double and triple word bonuses are stored for later computation
            for(int i = 0; i < length; i++){
                if(endTile.bonus == 0){
                    score += weight(endTile.letter);
                }else if(endTile.bonus == 2 || endTile.bonus == 3){
                    score += (weight(endTile.letter)*endTile.bonus);
                }else if(endTile.bonus == 4){
                    score += weight(endTile.letter);
                    doubleWord += 1;
                }else if(endTile.bonus == 9){
                    score += weight(endTile.letter);
                    tripleWord += 1;
                }
                //Move endTile over by 1 to the left
                endTile = tempBoard.getTile(endTile.coords.at(0)-1, y);
            }
                
            //adds score of adjacent connected letters above each letter in the word to the total score
            Tile above = tempBoard.getTile(endTile.coords.at(0), endTile.coords.at(1)-1);
            if(above.letter != 0){
                while(above.coords.at(1) >= 0 && above.letter != 0){
                    score += weight(above.letter);
                    above = tempBoard.getTile(above.coords.at(0), above.coords.at(1) - 1);
                }
            }
                
            Tile below = tempBoard.getTile(endTile.coords.at(0), endTile.coords.at(1)+1);
            if(below.letter != 0){
                while(below.coords.at(1) <= 15 && below.letter != 0){
                    score += weight(below.letter);
                    below = tempBoard.getTile(above.coords.at(0), above.coords.at(1) + 1);
                }
            }
        }
        
        
        //Word is vertically oriented 
        else if (endTile.orient == 2){
            //Places tiles onto a temporary side board in order to compute values of all
            //letters in the board in place
            for(int i = length; i >= 0; i--){
                tempBoard.tiles.at(15*y + x).letter = partialWord.at(i);
                y -= 1; 
            }
            //Computes the score of each letter including double and triple letter bonuses
            //Double and triple word bonuses are stored for later computation
            for(int i = 0; i < length; i++){
                if(endTile.bonus == 0){
                    score += weight(endTile.letter);
                }else if(endTile.bonus == 2 || endTile.bonus == 3){
                    score += (weight(endTile.letter)*endTile.bonus);
                }else if(endTile.bonus == 4){
                    score += weight(endTile.letter);
                    doubleWord += 1;
                }else if(endTile.bonus == 9){
                    score += weight(endTile.letter);
                    tripleWord += 1;
                }
                //Move endTile over by 1 up
                endTile = tempBoard.getTile(x, endTile.coords.at(1)-1);
            }
                
                
            Tile left = tempBoard.getTile(x - 1, endTile.coords.at(1));
            if(left.letter != 0){
                while(left.coords.at(0) >= 0 && left.letter != 0){
                    score += weight(left.letter);
                    left = tempBoard.getTile(left.coords.at(0) - 1, left.coords.at(1));
                }
            }
                
            Tile right = tempBoard.getTile(x + 1, endTile.coords.at(1));
            if(right.letter != 0){
                while(right.coords.at(0) <= 15 && right.letter != 0){
                    score += weight(right.letter);
                    right = tempBoard.getTile(right.coords.at(0) + 1, right.coords.at(1));
                }
            }
        }
        
        if(doubleWord > 0){
            score = score*2*doubleWord;
        }
        if(tripleWord > 0){
            score = score*3*tripleWord;
        }
        return score;
        
    }