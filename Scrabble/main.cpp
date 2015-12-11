#include <iostream>
#include "./board/consumer.cpp"
// This is basically going to be like an API
// Tie multiple discrete parts together to form
// a whole. int main() is actually the initializer
// for the entire "Scrabble" app. It is here where
// we will initialize the rest of the parts.

int main() {
    Board board = boardGen();
    cout << "This is the board loaded from the file:" << endl;
    // showboard(board);
    
    vector<Tile> rack = rackGen();
    vector<Board> answers;
    answers = movesGen(board, rack); //returns a vector of boards... we need to then display them.
    for (int i = 0; i < answers.size(); i++){
        // allow user to select a legal move and add it to the board
        // cout the board again with showboard(board)
    }
}
