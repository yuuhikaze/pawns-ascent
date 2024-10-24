#include "knight.h"
#include "../board.h"

Knight::Knight(bool is_white): Piece('n', is_white);

Knight::is_movement_valid(int origin_x, int origin_y, int target_x, int target_y, Board &board) const override {
        return true;
    }