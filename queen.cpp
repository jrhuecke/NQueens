#include "queen.h"
#include <fstream>
#include <iostream>

using namespace std;

bool Queen :: attackable(int x, int y) {
  //checking if queen is in same row or column
  if (x == col or y == row) {
    return true;
  }
  //checking diagonals
  if (abs(x-col) == abs(y-row)) {
    return true;
  }
  return false;
}


