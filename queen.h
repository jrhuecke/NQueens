#ifndef QUEEN_H
#define QUEEN_H

class Queen {
  public:
    int col;
    int row;
    bool attackable(int, int);
};


#endif