#ifndef QUEEN_H
#define QUEEN_H

#include "../piece.h"
using namespace std;

class Queen : public Piece {
public:
    Queen(bool is_white): Piece('q', is_white) {}

    bool is_movement_valid(int origin_x, int origin_y, int target_x, int target_y, const vector<vector<Piece *>> &board) override {
        
        vector<int> displacement =  calc_displacement(origin_x, origin_y, target_x, target_y);
        int delta_x = displacement[0];
        int delta_y = displacement[1];

        if(abs(delta_x) == abs(delta_y)) {

            int i = delta_x < 0 ? origin_x - 1: origin_x + 1;
            int step_x = delta_x < 0 ? -1: 1;

            int j = delta_y < 0 ? origin_y - 1: origin_y + 1;
            int step_y = delta_y < 0 ? -1: 1;
                
            while(i < target_x || j < target_y) {
                if(board[i][j] != nullptr) {
                    //Testing message. Please remove later
                    cout << "There is a piece blocking the way (diagonal)" << endl;
                    return false;
                }
                i += step_x;
                j += step_y;
            }

            if(board[target_x][target_y] == nullptr) return true; 
        
            if(board[target_x][target_y]->getis_white() == getis_white()) {
                //Testing message. Please remove later
                cout << "There is a piece blocking the way (diagonal)" << endl;
                return false; 
            }

            return true;
        }

        if(delta_x == 0 || delta_y == 0){
            if(delta_x != 0) {
                int i = delta_x < 0 ? origin_x - 1: origin_x + 1;
                int step_x = delta_x < 0 ? -1: 1;
                
                while(i < target_x) {
                    if(board[i][origin_y] != nullptr) {
                        cout << "There is a piece blocking the way (x)" << endl;
                        return false;
                    }
                    i += step_x;
                }

                if(board[target_x][target_y] == nullptr) return true; 
            
                if(board[target_x][target_y]->getis_white() == getis_white()) {
                    //Testing message. Please remove later
                    cout << "There is a piece blocking the way(x)" << endl;
                    return false; 
                }

                return true;
            }

            else {
                int j = delta_y < 0 ? origin_y - 1: origin_y + 1;
                int step_y = delta_y < 0 ? -1: 1;

                while(j < target_y) {
                    if(board[origin_x][j] != nullptr) {
                        cout << "There is a piece blocking the way(y)" << endl;
                        return false;
                    }
                    j += step_y;
                }

                if(board[target_x][target_y] == nullptr) return true; 
            
                if(board[target_x][target_y]->getis_white() == getis_white()) {
                    //Testing message. Please remove later
                    cout << "There is a piece blocking the way(y)" << endl;
                    return false; 
                }

                return true;
            }
        }
        return false;
    }
};

#endif //QUEEN.H