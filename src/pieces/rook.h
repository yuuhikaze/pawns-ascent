#ifndef ROOK_H
#define ROOK_H

#include "../piece.h"
using namespace std;

class Rook : public Piece {
public:
    Rook(bool is_white) : Piece('r', is_white) {}

    bool is_movement_valid(coordinates origin, coordinates target, const vector<vector<Piece *>> &board) override {
        
        vector<int> displacement = calc_displacement(origin, target);
        int delta_x = displacement[0];
        int delta_y = displacement[1];

        if(delta_x != 0 && delta_y != 0) {
            cout << "Not a straight line movement" << endl;
            return false;
        }
            
        if(delta_x != 0) {
            int i = delta_x < 0 ? origin.x - 1: origin.x + 1;
            int step_x = delta_x < 0 ? -1: 1;
            
            while(i < target.x) {
                if(board[i][origin.y] != nullptr) {
                    cout << "There is a piece blocking the way" << endl;
                    return false;
                }
                i += step_x;
            }

            if(board[target.x][target.y] == nullptr) return true; 
        
            if(board[target.x][target.y]->getis_white() == getis_white()) {
            //Testing message. Please remove later
            cout << "There is a piece blocking the way" << endl;
            return false; 
            }

            return true;
        }

        else {
            int j = delta_y < 0 ? origin.y - 1: origin.y + 1;
            int step_y = delta_y < 0 ? -1: 1;

            while(j < target.y) {
                if(board[origin.x][j] != nullptr) {
                    cout << "There is a piece blocking the way" << endl;
                    return false;
                }
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
    }
};

#endif //ROOK.H