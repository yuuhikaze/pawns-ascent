#ifndef QUEEN_H
#define QUEEN_H

#include "../piece.h"
using namespace std;

class Queen : public Piece {
  public:
    Queen(bool is_white): Piece('q', is_white) {}

    bool is_movement_valid(int origin_x, int origin_y, int target_x, int target_y, const vector<vector<Piece *>> &board) const override {
        return true;
    }
};

#endif //QUEEN.H