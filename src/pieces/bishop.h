#ifndef BISHOP_H
#define BISHOP_H

#include "../piece.h"
using namespace std;

class Board;

class Bishop : public Piece {
public:
    Bishop(bool is_white): Piece('b', is_white) {}

    bool is_movement_valid(coordinates origin, coordinates target, const vector<vector<Piece *>> &board) override {
        vector<int> displacement =  calc_displacement(origin, target);
        int delta_x = displacement[0];
        int delta_y = displacement[1];

        if(abs(delta_x) != abs(delta_y)) {
            //Testing message. Please remove later
            cout << "Not a diagonal move" << endl;
            return false;
        }

        int i = delta_x < 0 ? origin.x - 1: origin.x + 1;
        int step_x = delta_x < 0 ? -1: 1;

        int j = delta_y < 0 ? origin.y - 1: origin.y + 1;
        int step_y = delta_y < 0 ? -1: 1;
            
        while(i < target.x || j < target.y) {

            if(board[i][j] != nullptr) {
                //Testing message. Please remove later
                cout << "There is a piece blocking the way" << endl;
                return false;
            }
            i += step_x;
            j += step_y;
        }

        if(board[target.x][target.y] == nullptr) return true; 
        
        if(board[target.x][target.y]->getis_white() == getis_white()) {
            //Testing message. Please remove later
            cout << "There is a piece blocking the way" << endl;
            return false; 
        }

        return true;

    }
};

#endif //BISHOP.H