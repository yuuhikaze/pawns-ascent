#include "rook.h"
#include "../board.h"

Rook::Rook(bool is_white) : Piece('r', is_white) {}

bool Rook::is_movement_valid(int origin_x, int origin_y, int target_x, int target_y, Board &board) const override {
        return true;
    }