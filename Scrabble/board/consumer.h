// Info taken from these sites:
// http://www.learncpp.com/cpp-tutorial/19-header-files/
// http://www.umich.edu/~eecs381/handouts/CppHeaderFileGuidelines.pdf

// This is start of the header guard.  
#ifndef FSTREAM_I
#define FSTREAM_I
#include <fstream>
#endif
#ifndef IOSTREAM_I
#define IOSTREAM_I
#include <iostream>
#endif
#ifndef STRING_I
#define STRING_I
#include <string>
#endif
#ifndef VECTOR_I
#define VECTOR_I
#include <vector>
#endif
/*
#ifndef WEIGHT_H // not sure how to do this, one site says not to...
#define WEIGHT_H
#include "../lib/weight.cpp"
#endif
*/
// ***_H can be any unique name.  By convention, we use the name of the header file.
#ifndef BOARDGEN_H
#define BOARDGEN_H

// This is the content of the .h file, which is where the declarations go
Board boardGen();
vector<Tile> rackGen();

// This is the end of the header guard
#endif