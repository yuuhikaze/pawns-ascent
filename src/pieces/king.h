#ifndef KING_H
#define KING_H

#include "piece.h"

class Board;

class King : public Piece {
  public:
    King(bool is_white);

    bool is_movement_valid(int origin_x, int origin_y, int target_x, int target_y, Board &board);
};

#endif //KING.H
