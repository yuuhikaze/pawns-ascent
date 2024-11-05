#ifndef ROOK_H
#define ROOK_H

#include "../piece.h"
using namespace std;

class Rook : public Piece {
public:
    Rook(bool is_white) : Piece('r', is_white) {}

    bool is_movement_valid(int origin_x, int origin_y, int target_x, int target_y, const vector<vector<Piece *>> &board) override {
        
        vector<int> displacement = calc_displacement(origin_x, origin_y, target_x, target_y);
        int delta_x = displacement[0];
        int delta_y = displacement[1];

        if(delta_x != 0 && delta_y != 0) {
            cout << "Not a straight line movement" << endl;
            return false;
        }
            
        if(delta_x != 0) {
            int i = delta_x < 0 ? origin_x - 1: origin_x + 1;
            int step_x = delta_x < 0 ? -1: 1;
            
            while(i < target_x) {
                if(board[i][origin_y] != nullptr) {
                    cout << "There is a piece blocking the way" << endl;
                    return false;
                }
                i += step_x;
            }

            if(board[target_x][target_y] == nullptr) return true; 
        
            if(board[target_x][target_y]->getis_white() == getis_white()) {
            //Testing message. Please remove later
            cout << "There is a piece blocking the way" << endl;
            return false; 
            }

            return true;
        }

        else {
            int j = delta_y < 0 ? origin_y - 1: origin_y + 1;
            int step_y = delta_y < 0 ? -1: 1;

            while(j < target_y) {
                if(board[origin_x][j] != nullptr) {
                    cout << "There is a piece blocking the way" << endl;
                    return false;
                }
                j += step_y;
            }

            if(board[target_x][target_y] == nullptr) return true; 
        
            if(board[target_x][target_y]->getis_white() == getis_white()) {
            //Testing message. Please remove later
            cout << "There is a piece blocking the way" << endl;
            return false; 
            }

            return true;
        }
    }
};

#endif //ROOK.H