#ifndef PAWN_H
#define PAWN_H

#include "Piece.h"
using namespace std;

class Pawn : public Piece {
  public:
    Pawn(char symbol, bool is_white) : Piece(symbol, is_white) {
      symbol = 'p';
    }

    bool is_movement_valid(int origin_x, int origin_y, int target_x, int target_y) const override {
        
        if (target_x > 7 || target_y > 7) return false;

        if(!hasMoved){
          
        }
        
        return true;
    }

  private:
    bool hasMoved = false;

};

#endif //PAWN.H