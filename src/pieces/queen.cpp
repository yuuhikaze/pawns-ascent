#include "queen.h"

Queen::Queen(bool is_white): Piece('q', is_white) {}

Queen::is_movement_valid(int origin_x, int origin_y, int target_x, int target_y, Board &board) const override {
        return true;
    }