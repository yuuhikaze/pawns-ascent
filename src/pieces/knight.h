#ifndef KNIGHT_H
#define KNIGHT_H

#include "../piece.h"
using namespace std;

class Knight : public Piece {
public:
    Knight(bool is_white): Piece('n', is_white) {}

    bool is_movement_valid(int origin_x, int origin_y, int target_x, int target_y, const vector<vector<Piece *>> &board) override {

        vector<int> displacement =  calc_displacement(origin_x, origin_y, target_x, target_y);
        int delta_x = displacement[0];
        int delta_y = displacement[1];

        if((abs(delta_x) != 1 || abs(delta_y) != 2) && (abs(delta_y) != 1 || abs(delta_x) != 2)){
            cout << "Not an L move" << endl;
            return false;
        }

        if(board[target_x][target_y] == nullptr) return true;
        
        if(board[target_x][target_y]->getis_white() == getis_white()) {
            cout << "There is a piece blocking the way" << endl;
            return false;
        }
        
        return true;

        }
};

#endif //KNIGHT_HS