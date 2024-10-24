#ifndef KNIGHT_H
#define KNIGHT_H

#include "piece.h"

class Board;

class Knight : public Piece {
  public:
    Knight(bool is_white);

    bool is_movement_valid(int origin_x, int origin_y, int target_x, int target_y, Board &board) const override;
};

#endif //KNIGHT_HS