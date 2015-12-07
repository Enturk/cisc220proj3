#include <iostream>
#include "./lib/structs.cpp"
#include "./board/consumer.cpp"
#include "./moves/movesGen.cpp"
// This is basically going to be like an API
// Tie multiple discrete parts together to form
// a whole. int main() is actually the initializer
// for the entire "Scrabble" app. It is here where 
// we will initialize the rest of the parts.

int main() {
    Board board = boardGen();
    Tile* rack = rackGen();
    Board* moves = movesGen();
    // Which do we want to do?
    cout << printBoard(moves[0]) << endl;
    cout << moves[0] << endl;
}
