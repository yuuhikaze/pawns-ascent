#ifndef PAWN_H
#define PAWN_H

#include "piece.h"

class Board;

class Pawn : public Piece {
  public:
    Pawn(bool is_white);

    bool is_movement_valid(int origin_x, int origin_y, int target_x, int target_y, Board &board) const override;

  private:
    bool hasMoved;

};

#endif //PAWN.H