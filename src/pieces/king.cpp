#include "king.h"
#include "../board.h"
using namespace std;

King::King(bool is_white): Piece('k', is_white) {}

King::is_movement_valid(int origin_x, int origin_y, int target_x, int target_y, Board &board) const override {
        return true;
    }