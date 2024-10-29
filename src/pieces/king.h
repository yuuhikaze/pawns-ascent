#ifndef KING_H
#define KING_H

#include "../piece.h"
using namespace std;

class King : public Piece {
  public:
    King(bool is_white): Piece('k', is_white) {}

    bool is_movement_valid(int origin_x, int origin_y, int target_x, int target_y, const vector<vector<Piece *>> &board) const override {
        return true;
    }
};

#endif //KING.H
