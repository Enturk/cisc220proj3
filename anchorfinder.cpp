#include <vector>
#include <map>
#include <fstream>
#include <iostream>
#include <cstdlib> // for exit()
#include "readboard.h"
using namespace std;

// function that returns a 2D array of booleans representing the vacant spots
// adjacent to an existing letter
bool anchorfinder(int* board[][]){
    bool anchor[14][14]; //or one array of 225 elements if Rile is right
    for (int i = 0; )
}