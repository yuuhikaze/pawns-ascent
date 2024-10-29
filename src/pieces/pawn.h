#ifndef PAWN_H
#define PAWN_H

#include "../piece.h"
using namespace std;

class Pawn : public Piece {
  public:
   Pawn(bool is_white): Piece('p', is_white) {}

    bool is_movement_valid(int origin_x, int origin_y, int target_x, int target_y, const vector<vector<Piece *>> &board) const override {
        return true;
    }

  private:
    bool hasMoved = false;

};

#endif //PAWN.H