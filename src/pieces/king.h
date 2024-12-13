#ifndef KING_H
#define KING_H

#include "../piece.h"
#include "knight.h"
#include "pawn.h"
#include "queen.h"
#include "rook.h"
#include "bishop.h"

using namespace std;

class King : public Piece {
  public:
    King(bool is_white) : Piece('k', is_white) {}

    bool is_movement_valid(coordinates origin, coordinates target, const vector<vector<Piece *>> &board) override {
        vector<int> displacement = calc_displacement(origin, target);
        int delta_x = displacement[0];
        int delta_y = displacement[1];

        if (abs(delta_x) > 1 || abs(delta_y) > 1)
            return false;

        if(!is_valid_tile(target, board)) {
            // Testing message. Please remove later
            cout << "There is a piece blocking the way" << endl;
            return false;
        } 

        if(is_checked(target, board)) {
            // Testing message. Please remove later
            cout << "You are checked" << endl;
            return false;
        }
        
        else {
            set_default_en_passant();
            if(getis_white())
                GameState::white_king = target;
            else
                GameState::black_king = target;
            return true;
        }
    }

    vector<coordinates> getmoves(coordinates origin, const vector<vector<Piece *>> &board) override {
        vector<coordinates> moves;

        if(origin.y < 7) {
            for(int i = origin.x - 1; i < origin.x + 2; i++) {
                if(is_valid_tile(coordinates(i, origin.y + 1), board))
                    if(!is_checked(coordinates(i, origin.y + 1), board))
                        moves.push_back(coordinates(i, origin.y + 1));
            }
        }

        if(origin.y > 0) {
            for(int i = origin.x - 1; i < origin.x + 2; i++) {
                if(is_valid_tile(coordinates(i, origin.y - 1), board))
                    if(!is_checked(coordinates(i, origin.y - 1), board))
                        moves.push_back(coordinates(i, origin.y - 1));
            }
        }

        if(is_valid_tile(coordinates(origin.x - 1, origin.y), board)) {
            if(!is_checked(coordinates(origin.x - 1, origin.y), board))
                moves.push_back(coordinates(origin.x - 1, origin.y));
        }

        if(is_valid_tile(coordinates(origin.x + 1, origin.y), board)) {
            if(!is_checked(coordinates(origin.x + 1, origin.y), board))
                moves.push_back(coordinates(origin.x + 1, origin.y));
        }
        
        return moves;
    }

};

#endif // KING.H
