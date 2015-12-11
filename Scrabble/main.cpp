#include <iostream>
#include "./board/consumer.cpp"
// #include <stdlib.h> if we want to clear the screen, we can use system("CLS");

// This is basically going to be like an API
// Tie multiple discrete parts together to form
// a whole. int main() is actually the initializer
// for the entire "Scrabble" app. It is here where
// we will initialize the rest of the parts.

int main() {
    bool PRINTBOARDS = true; // set to false if you don't want resulting top play boards to print out
    Board board = boardGen();
    cout << "This is the board loaded from the file:" << endl;
    board.print();
    
    vector<Tile> rack = rackGen();
    vector<Board> answers;
    answers = movesGen(board, rack); //returns a vector of boards... we need to then display them.
    int input = 3;
    // uncomment the below to have a UI that asks how many boards to print
    // cout << "how many of the top scoring plays do you want displayed on the board (enter a number less than 21)?" << endl;
    // cin >> input;
    for (int i = 0; i < 20; i++){
        //cout << answers.at(i).score << endl;
        if (i<input+1 && PRINTBOARDS){
            answers.at(i).print();
            cout << endl;
        }
    }
}
