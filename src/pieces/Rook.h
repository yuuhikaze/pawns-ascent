#ifndef ROOK_H
#define ROOK_H

#include "piece.h"
using namespace std;

class Board;

class Rook : public Piece {
  public:
    Rook(bool is_white);

    bool is_movement_valid(int origin_x, int origin_y, int target_x, int target_y, Board &board);
};

#endif //ROOK.H