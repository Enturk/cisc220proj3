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
   // board.print();
    
    vector<Tile> rack = rackGen();
    vector<Board> answers;
    answers = movesGen(board, rack); //returns a vector of boards... we need to then display them.
    int input = 20;
    // cout << "how many of the top scoring plays do you want displayed on the board (enter a number less than 21)?" << endl;
    // cin >> input;
    for (int i = 0; i < 20; i++){
        cout << answers.at(i).score << endl;
        if (i<input+1) answers.at(i).print();
        cout << endl;
    }
}
