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
<<<<<<< HEAD
    vector<Tile> anchors = getAnchors(board);
    for (int i = 0; i < anchors.size(); i++){
      cout << anchors.at(i).coords.at(0) << "," << anchors.at(i).coords.at(1);
    }
    //vector<Board> moves = movesGen(board, rack);
    // the only thing left to do is sort moves by move.score.
    //cout << moves[0] << endl;
=======
    vector<Board> moves = movesGen(board, rack);
    vector<Board> bestmoves = findBest(moves);
    cout << moves[0] << endl;
>>>>>>> daeaec4260354790be8dc5322839ee1c824b78d7
}
