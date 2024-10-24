#include "bishop.h"
#include "../board.h"
using namespace std;

Bishop::Bishop(bool is_white): Piece('b', is_white) {}

bool Bishop::is_movement_valid(int origin_x, int origin_y, int target_x, int target_y, Board &board) const override {
        return true;
    }