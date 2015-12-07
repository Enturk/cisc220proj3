#include <iostream>
using namespace std;

// this function simply returns the score value of any letter

int weight(char letter){
    switch (letter){
        case 'A':
            return 1;
            break;
        case 'B':
            return 3;
            break;
        case 'C':
            return 3;
            break;
        case 'D':
            return 2;
            break;
        case 'E':
            return 1;
            break;
        case 'F':
            return 4;
            break;
        case 'G':
            return 2;
            break;
        case 'H':
            return 4;
            break;
        case 'I':
            return 1;
            break;
        case 'J':
            return 8;
            break;
        case 'K':
            return 5;
            break;
        case 'L':
            return 1;
            break;
        case 'M':
            return 3;
            break;
        case 'N':
            return 1;
            break;
        case 'O':
            return 1;
            break;
        case 'P':
            return 3;
            break;
        case 'Q':
            return 10;
            break;
        case 'R':
            return 1;
            break;
        case 'S':
            return 1;
            break;
        case 'T':
            return 1;
            break;
        case 'U':
            return 1;
            break;
        case 'V':
            return 4;
            break;
        case 'W':
            return 4;
            break;
        case 'X':
            return 8;
            break;
        case 'Y':
            return 4;
            break;
        case 'Z':
            return 10;
            break;
        case '*':
            return 0;
            break;
    }
    return 0;
}

int main (){
    // testing
    char testingLet = 'R';
    cout << "The score value of " << testingLet << " is " << weight(testingLet) << endl;
}