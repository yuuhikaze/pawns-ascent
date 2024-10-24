#ifndef QUEEN_H
#define QUEEN_H

#include "piece.h"

class Board;

class Queen : public Piece {
  public:
    Queen(bool is_white);

    bool is_movement_valid(int origin_x, int origin_y, int target_x, int target_y, Board &board);
};

#endif //QUEEN.H