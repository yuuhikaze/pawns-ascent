#ifndef ROOK_H
#define ROOK_H

#include "../piece.h"
using namespace std;

class Rook : public Piece {
  public:
    Rook(bool is_white) : Piece('r', is_white) {}

    bool is_movement_valid(int origin_x, int origin_y, int target_x, int target_y, const vector<vector<Piece *>> &board) const override {
        return true;
    }
};

#endif //ROOK.H