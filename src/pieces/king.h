#ifndef KING_H
#define KING_H

#include "../piece.h"
using namespace std;

class King : public Piece {
public:
    King(bool is_white): Piece('k', is_white) {}

    bool is_movement_valid(int origin_x, int origin_y, int target_x, int target_y, const vector<vector<Piece *>> &board) override {
        vector<int> displacement =  calc_displacement(origin_x, origin_y, target_x, target_y);
        int delta_x = displacement[0];
        int delta_y = displacement[1];

        if(abs(delta_x) != 1 || abs(delta_y) != 1) return false;

        return true;
    }
};

#endif //KING.H
