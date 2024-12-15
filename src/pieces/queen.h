#ifndef QUEEN_H
#define QUEEN_H

#include "../piece.h"
using namespace std;

class Queen : public Piece {
  public:
    Queen(bool is_white) : Piece('q', is_white) {}

    bool is_movement_valid(coordinates origin, coordinates target, const vector<vector<Piece *>> &board) override {

        vector<int> displacement = calc_displacement(origin, target);
        int delta_x = displacement[0];
        int delta_y = displacement[1];

        if (abs(delta_x) == abs(delta_y)) {

            int step_x = delta_x > 0 ? 1 : -1;
            int step_y = delta_y > 0 ? 1 : -1;
        
            int i = origin.x + step_x;
            int j = origin.y + step_y;

            while (i < target.x && j < target.y) {
                if (board[i][j] != nullptr) {
                    // Testing message. Please remove later
                    cout << "There is a piece blocking the way (diagonal)" << endl;
                    return false;
                }
                i += step_x;
                j += step_y;
            }

            if(is_valid_tile(target, board)) {
                set_default_en_passant();
                return true;
            }

            else {
                // Testing message. Please remove later
                cout << "There is a piece blocking the way" << endl;\
                return false;
            }
        }

        if (delta_x == 0 || delta_y == 0) {
            if (delta_x != 0) {
                int step_x = delta_x > 0 ? 1 : -1;
                int i = origin.x + step_x;

                while (i < target.x) {
                    if (board[i][origin.y] != nullptr) {
                        cout << "There is a piece blocking the way (x)" << endl;
                        return false;
                    }
                    i += step_x;
                }

                if(is_valid_tile(target, board)) {
                    set_default_en_passant();
                    return true;
                }

                else {
                    // Testing message. Please remove later
                    cout << "There is a piece blocking the way" << endl;
                    return false;
                }
            }

            else {
                int step_y = delta_y > 0 ? 1 : -1;
                int j = origin.y + step_y;

                while (j < target.y) {
                    if (board[origin.x][j] != nullptr) {
                        cout << "There is a piece blocking the way(y)" << endl;
                        return false;
                    }
                    j += step_y;
                }

                if(is_valid_tile(target, board)) {
                    set_default_en_passant();
                    return true;
                }

                else {
                    // Testing message. Please remove later
                    cout << "There is a piece blocking the way" << endl;
                    return false;
                }
            }
        }
        return false;
    }

    vector<coordinates> getmoves(coordinates origin, const vector<vector<Piece *>> &board) override {
        vector<coordinates> temp_moves;
        vector<coordinates> moves;

        moves = gethorizontal_LOS(origin, true, board);
        if(!moves.empty())
            if(!is_valid_tile(moves.back(), board))
                moves.pop_back();

        temp_moves = getdiagonal_LOS(origin, true, true, board);
        if(!temp_moves.empty()) {
            if(!is_valid_tile(temp_moves.back(), board))
                temp_moves.pop_back();
            moves.insert(moves.end(), temp_moves.begin(), temp_moves.end());
        }

        temp_moves = getvertical_LOS(origin, true, board);
        if(!temp_moves.empty()) {
            if(!is_valid_tile(temp_moves.back(), board))
                temp_moves.pop_back();
            moves.insert(moves.end(), temp_moves.begin(), temp_moves.end());
        }

        temp_moves = getdiagonal_LOS(origin, false, true, board);
        if(!temp_moves.empty()) {
            if(!is_valid_tile(temp_moves.back(), board))
                temp_moves.pop_back();
            moves.insert(moves.end(), temp_moves.begin(), temp_moves.end());
        }

        temp_moves = gethorizontal_LOS(origin, false, board);
        if(!temp_moves.empty()) {
            if(!is_valid_tile(temp_moves.back(), board))
                temp_moves.pop_back();
            moves.insert(moves.end(), temp_moves.begin(), temp_moves.end());
        }

        temp_moves = getdiagonal_LOS(origin, false, false, board);
        if(!temp_moves.empty()) {
            if(!is_valid_tile(temp_moves.back(), board))
                temp_moves.pop_back();
            moves.insert(moves.end(), temp_moves.begin(), temp_moves.end());
        }

        temp_moves = getvertical_LOS(origin, false, board);
        if(!temp_moves.empty()) {
            if(!is_valid_tile(temp_moves.back(), board))
                temp_moves.pop_back();
            moves.insert(moves.end(), temp_moves.begin(), temp_moves.end());
        }

        temp_moves = getdiagonal_LOS(origin, true, false, board);
        if(!temp_moves.empty()) {
            if(!is_valid_tile(temp_moves.back(), board))
                temp_moves.pop_back();
            moves.insert(moves.end(), temp_moves.begin(), temp_moves.end());
        }
        
        return moves;
    }
};

#endif // QUEEN.H
