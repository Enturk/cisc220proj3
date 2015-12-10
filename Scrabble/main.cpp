#include <iostream>
#include "./board/consumer.cpp"
#include "./moves/movesGen.cpp"
// This is basically going to be like an API
// Tie multiple discrete parts together to form
// a whole. int main() is actually the initializer
// for the entire "Scrabble" app. It is here where
// we will initialize the rest of the parts.

int main() {
    Board board = boardGen();
    vector<Tile> rack = rackGen();
    vector<Tile> anchors = getAnchors(board);
    
    for (int i = 0; i < anchors.size(); i++){ //to test getAnchors
      cout << anchors.at(i).coords.at(0) << "," << anchors.at(i).coords.at(1);
    }
    
    string partial = findPartial(anchors.at(0), board); //test
    
    int limit = findLimit(anchor.at(0), board); //test
    
    //vector<Board> moves = movesGen(board, rack);
    // the only thing left to do is sort moves by move.score.
    //cout << moves[0] << endl;
    
     //idk who wrote this ^^^ bit but that is taken care of in movesGen now! -Sam
    
    vector<Board> answers;
    answers = movesGen(board, rack); //returns a vector of boards... we need to then display them.
    for (int i = 0; i < answers.size(); i++){
        cout << answers.at(i); //if riley's overloader works this will print all them out
    }
    //vector<Board> moves = movesGen(board, rack);
    // the only thing left to do is sort moves by move.score.
    //cout << moves[0] << endl;
}
