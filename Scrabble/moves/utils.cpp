#include <iostream>
#include <string.h>
#include <vector>
#include <bitset>
#include <map>
#include <fstream>
#include <algorithm>
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

string findPartial(Tile anchor, vector<Tile> row){
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
     int x=anchor.coords.at(dir-1);
     if(x==0)return "";
     int i= x-1;
     string out;
     for(i;row.at(i).letter!=0&&i>0;i--);//
     for(i;i<x;i++){
        out.append(string(1,row.at(i).letter));
     }
     if(out[0]==0)out=out.substr(1,out.size()-1);
     return out;
}

void crossCheck(Tile& tile, Board& board){
    // Nazim
    /* Need to deal with orientation and other side of the tile
    tile.orient is 1 if just horizontal, 2 if just vertical, 3 if both
    Scenario 1 passes orient 1 (taken care of automatically)
    after running partial word horizontally (if necessary) => result 1
    do get col, run findPartial on the right tile => result 2
    loop tile.xchecks to result 1 AND result 2
    */
  Trie trie = getTrie();
  string word;
  string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  
  vector<Tile> row;
  if(tile.orient==1)row = board.getRow(tile.coords[1]);
  else if(tile.orient==2)row = board.getCol(tile.coords[0]);
  
  string leftSide = findPartial(tile, row);
  
  reverse(row.begin(),row.end());
  
  tile.coords.at(tile.orient-1)=14-tile.coords.at(tile.orient-1);
  
  string rightSide = findPartial(tile, row);
  reverse(rightSide.begin(),rightSide.end());
  
  reverse(row.begin(),row.end());
  tile.coords.at(tile.orient-1)=14-tile.coords.at(tile.orient-1);
  //cout << "xcheck at ("<<tile.coords[0]<<","<<tile.coords[1]<<");"<<tile.orient<<": "<<leftSide<<"_"<<rightSide<<endl;
  
  bitset<26> old = tile.xchecks;
  for (int i = 0; i < 26; i++){
      int wordLength = leftSide.length()+1+rightSide.length();
      word = leftSide + alphabet[i] + rightSide;
      char * y = new char[wordLength+1];
      copy(word.begin(),word.end(),y);
      y[wordLength] = '\0';
      tile.xchecks[i] = trie.hasWord(y, wordLength); // I'm a genius. That's Nazim. He really is.
      delete[] y;
  }
  tile.xchecks = tile.xchecks & old;
}

vector<Tile> getAnchors(Board& board){
    //Sam
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
    
    for (int i = 0; i< 15; i++){ //rows
        vector<Tile> row = board.getRow(i);
        vector<Tile> col = board.getCol(i);
        for (int j = 0; j < 14; j++){
            if (row.at(j).letter == 0 && isalpha(row.at(j+1).letter)){ //checks if the tile is empty and the tile next to it has a letter
                board.getTile(j,i).orient = 1; //horizontal (the way the board normally looks)
                anchors.push_back(board.getTile(j,i));
            }
            else if (col.at(j).letter == 0 && isalpha(col.at(j+1).letter)){
                board.getTile(i,j).orient = 2; //vertically
                if(i==0&&j==11)cout << "ZERO ELEVEN"<<board.getTile(i,j).orient<<endl;
                anchors.push_back(board.getTile(i,j));
            }
            
        }
    }
    //cross checks everything that is adjacent to a filled tile.
    for (int j = 0; j < 15; j++){
        vector<Tile> row = board.getRow(j);
        vector<Tile> col = board.getCol(j);
        for (int i =0; i < 15; i++){
            if (i ==0){
                if (row.at(i).letter == 0 && (isalpha(row.at(i+1).letter))){
                    board.getTile(j,i).orient = 1;
                    crossCheck(board.getTile(j,i), board);
                }
                if (col.at(i).letter == 0 && (isalpha(col.at(i+1).letter))){
                    board.getTile(i,j).orient = 2;
                    crossCheck(board.getTile(i,j), board);
                }
            }
            else if (i ==14){
                if (row.at(i).letter == 0 && (isalpha(row.at(i-1).letter))){
                    board.getTile(j,i).orient = 1;
                    crossCheck(board.getTile(j,i), board);
                }
                if (col.at(i).letter == 0 && (isalpha(col.at(i-1).letter))){
                    board.getTile(i,j).orient = 2;
                    crossCheck(board.getTile(i,j), board);
                }
            }
            else {
                if (row.at(i).letter == 0 && (isalpha(row.at(i+1).letter) || isalpha(row.at(i-1).letter))){
                    board.getTile(j,i).orient = 1;
                    crossCheck(board.getTile(j,i), board);
                }
                if (col.at(i).letter == 0 && (isalpha(col.at(i+1).letter) || isalpha(col.at(i-1).letter))){
                    board.getTile(i,j).orient = 2;
                    crossCheck(board.getTile(i,j), board);
                }
            }
        }
    }
    for (int i = 0; i < anchors.size(); i++){ // runs xcheck on all the anchors
        if ((anchors.at(i).xchecks).count() !=0){ //checks to make sure the bitset isn't trivial (all 0s)
            finalAnchs.push_back(anchors.at(i));
        }
    }
    for (int i = 0; i<finalAnchs.size(); i++){
        finalAnchs.at(i).anchor = true;
    }
    cout << "anchor 0,11 orient: " << finalAnchs[0].orient << endl;
    return finalAnchs;
}



int findLimit(Tile anchor, vector<Tile> row){
    //Sam
    /* args: Tile anchor, the anchor we want to find the left limit of.
     *       Board board, the board to analyze
     * returns: the number of non-anchor tiles to the left of anchor.
     */
    int limit = 0;
    int xcoord = anchor.coords.at(anchor.orient-1);
    //find the coordinate of the anchor on the board
    //check from the anchor to the beginning of the row to add to limit count
    //if it reaches another anchor limit is stopped
    for (int i = xcoord; i > 0; i--){
        //stops the limit count if it hits another anchor
        if (row.at(i).anchor){
            return limit;
        }
        //increases the limit count for each non-anchor tile left of it that it reaches
        else{
            limit++;
        }
    }
    return limit;
}

vector<int> scoreit(Tile t){
        vector<int> ans(4);
        if (t.bonus ==0){
          ans.at(0) += t.weight;
        }
        if (t.bonus == 2){
          ans.at(0) += t.bonus * t.weight;
        }
        if (t.bonus == 3){
          ans.at(0) += t.bonus * t.weight;
        }
        if (t.bonus == 3){
          ans.at(1)++;
        }
        if (t.bonus == 4){
          ans.at(2)++;
        }
        if (t.letter == 0){
          ans.at(3)++;
        }
    return ans;
}

int getScore(string partialWord, Board board, Tile end){
        //Josh
        /* ARGS: partialWord; legal partial word combination formed from rack tiles
         *       board; current board
         *       endTile; last tile of the word in question
         *RETURNS: The score of the playable word
         */
        Board tempBoard = board;
        Tile endTile = end;
        int score = 0;
        int doublebonus = 0;
        int triplebonus = 0;
        int rack = 0;
        int xcoord = endTile.coords.at(0);
        int ycoord = endTile.coords.at(1);
        int length = partialWord.length();
        //If the word is horizontally oriented, this is the right-most board letter of the word
        if (endTile.orient = 1){
            for (int i = 0; i < length; i++){
                Tile temp = board.getTile(xcoord-i, ycoord);
                vector<int> scoreDoubTripRack(4);
                scoreDoubTripRack = scoreit(temp);
                score += scoreDoubTripRack.at(0);
                doublebonus += scoreDoubTripRack.at(1);
                triplebonus += scoreDoubTripRack.at(2);
                rack += scoreDoubTripRack.at(3);

                tempBoard.getTile(xcoord-i, ycoord).letter = partialWord.at(length-1-i);
                int j = 1;
                while (isalpha(tempBoard.getTile(xcoord, ycoord +j).letter) && (ycoord + j) <15){
                  score += tempBoard.getTile(xcoord, ycoord +j).weight;
                  j++;
                }
                while (isalpha(tempBoard.getTile(xcoord, ycoord -j).letter) && (ycoord - j) >=0){
                  score += tempBoard.getTile(xcoord, ycoord -j).weight;
                  j++;
                }
                
            }
        }
        if (endTile.orient = 2){
            for (int i = 0; i < length; i++){
                Tile temp = board.getTile(xcoord, ycoord-i);
                vector<int> scoreDoubTripRack(4);
                scoreDoubTripRack = scoreit(temp);
                score += scoreDoubTripRack.at(0);
                doublebonus += scoreDoubTripRack.at(1);
                triplebonus += scoreDoubTripRack.at(2);
                rack += scoreDoubTripRack.at(3);

                tempBoard.getTile(xcoord, ycoord-i).letter = partialWord.at(length-1-i);
                int j = 1;
                while (isalpha(tempBoard.getTile(xcoord + j, ycoord).letter) && (ycoord + j) <15){
                  score += tempBoard.getTile(xcoord+ j, ycoord).weight;
                  j++;
                }
                while (isalpha(tempBoard.getTile(xcoord-j, ycoord).letter) && (ycoord - j) >=0){
                  score += tempBoard.getTile(xcoord-j, ycoord).weight;
                  j++;
                }
                
            }
          if(doublebonus > 0){
              score = score*2*doublebonus;
          }
          if(triplebonus > 0){
              score = score*3*triplebonus;
          }
          if(rack == 7){
              score += 50;
          }
          return score;

    }
}