#include "pawn.h"
#include "../board.h"

Pawn::Pawn(is_white): Piece('p', is_white) {}

Pawn::is_movement_valid(int origin_x, int origin_y, int target_x, int target_y, Board &board) const override {
        return true;
    }

Pawn::hasMoved = false;