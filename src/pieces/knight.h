#ifndef KNIGHT_H
#define KNIGHT_H

#include "../piece.h"
#include <algorithm>
using namespace std;

class Knight : public Piece {
  public:
    Knight(bool is_white) : Piece('n', is_white) {}

    bool is_movement_valid(coordinates origin, coordinates target, const vector<vector<Piece *>> &board) override {

        vector<int> displacement = calc_displacement(origin, target);
        int delta_x = displacement[0];
        int delta_y = displacement[1];

        if ((abs(delta_x) != 1 || abs(delta_y) != 2) && (abs(delta_y) != 1 || abs(delta_x) != 2)) {
            cout << "Not an L move" << endl;
            return false;
        }

        if (is_valid_tile(target, board)) {
            set_default_en_passant();
            return true;
        }

         else {
            // Testing message. Please remove later
            cout << "There is a piece blocking the way" << endl;
            return false;
        }
    }

    vector<coordinates> getmoves(coordinates origin, const vector<vector<Piece *>> &board) override {
        vector<coordinates>moves = getL_LOS(origin, board);
        if(moves.empty())
            return moves;

    auto it = std::remove_if(moves.begin(), moves.end(), 
        [&board, this](const coordinates &move) {
            return !this->is_valid_tile(move, board);
        });
        moves.erase(it, moves.end());
        return moves;
    }
};

#endif // KNIGHT_HS
