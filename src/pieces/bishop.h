#ifndef BISHOP_H
#define BISHOP_H

#include "piece.h"

class Board;

class Bishop : public Piece {
  public:
    Bishop(bool is_white);

    bool is_movement_valid(int origin_x, int origin_y, int target_x, int target_y, Board &board) const override;
};

#endif //BISHOP.H