#ifndef KING_H
#define KING_H

#include "../piece.h"
using namespace std;

class King : public Piece {
private:
    


public:
    King(bool is_white): Piece('k', is_white) {}

    bool is_movement_valid(coordinates origin, coordinates target, const vector<vector<Piece *>> &board) override {
        vector<int> displacement =  calc_displacement(origin, target);
        int delta_x = displacement[0];
        int delta_y = displacement[1];

        if(abs(delta_x) != 1 || abs(delta_y) != 1) return false;

        return true;
    }
};

#endif //KING.H
