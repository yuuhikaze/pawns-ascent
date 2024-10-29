#ifndef KNIGHT_H
#define KNIGHT_H

#include "../piece.h"
using namespace std;

class Knight : public Piece {
  public:
    Knight(bool is_white): Piece('n', is_white) {}

    bool is_movement_valid(int origin_x, int origin_y, int target_x, int target_y, const vector<vector<Piece *>> &board) const override {
        return true;
    }
};

#endif //KNIGHT_HS