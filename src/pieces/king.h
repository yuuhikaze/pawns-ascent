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
        
        return true;
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

    bool is_checked(const coordinates &target, const vector<vector<Piece *>> &board) {
        
        if(is_checked_diagonal(target, true, true, board))
            return true;
        
        if(is_checked_diagonal(target, true, false, board))
            return true;
        
        if(is_checked_diagonal(target, false, false, board))
            return true;
        
        if(is_checked_diagonal(target, false, true, board))
            return true;

        if(is_checked_horizontal(target, true, board))
            return true;
        
        if(is_checked_horizontal(target, false, board))
            return true;
        
        if(is_checked_vertical(target, true, board))
            return true;

        if(is_checked_vertical(target, false, board))
            return true;
        
        if(is_checked_L(target, board))
            return true;
        
        return false;
    }

  private:
    bool is_checked_diagonal(coordinates origin, bool direction_x, bool direction_y, const vector<vector<Piece *>> &board) const {
        int step_x = direction_x ? 1 : -1;
        int step_y = direction_y ? 1 : -1;

        if(origin.x + step_x < 8 && origin.x + step_x > -1 && origin.y + step_y < 8 && origin.y + step_y > -1) {
            if(dynamic_cast<King *>(board[origin.x + step_x][origin.y + step_y]))
                if(board[origin.x + step_x][origin.y + step_y]->getis_white() == getis_white()) {
                    origin.x += step_x;
                    origin.y += step_y;
            }
        }

        vector<coordinates> moves = getdiagonal_moves(origin, direction_x, direction_y, board);
        if(moves.empty())
            return false;

        coordinates position = moves.back();
        if(dynamic_cast<Bishop *>(board[position.x][position.y]) || dynamic_cast<Queen *>(board[position.x][position.y]))
            return true;
        
        if(moves.size() == 1) {
            if(dynamic_cast<King *>(board[position.x][position.y]))
                return true;
            
            if(getis_white()) {
                if(direction_y && dynamic_cast<Pawn *>(board[position.x][position.y]))
                    return true;
            }

            else {
                if(!direction_y && dynamic_cast<Pawn *>(board[position.x][position.y]))
                    return true;
            }
        }

        return false;
    }

    bool is_checked_horizontal(coordinates origin, bool direction_x, const vector<vector<Piece *>> &board) const {
        int step_x = direction_x ? 1 : -1;

        if(origin.x + step_x > -1 && origin.x + step_x < 8) {
            if(dynamic_cast<King *>(board[origin.x + step_x][origin.y]))
                if(board[origin.x + step_x][origin.y]->getis_white() == getis_white())
                    origin.x += step_x;
        }

        vector<coordinates> moves = gethorizontal_moves(origin, direction_x, board);
        if(moves.empty())
            return false;

        coordinates position = moves.back();
        if(dynamic_cast<Rook *>(board[position.x][position.y]) || dynamic_cast<Queen *>(board[position.x][position.y]))
            return true;
        
        if(moves.size() == 1) {
            if(dynamic_cast<King *>(board[position.x][position.y]))
                return true;
        }

        return false;
    }

    bool is_checked_vertical(coordinates origin, bool direction_y, const vector<vector<Piece *>> &board) const {
        int step_y = direction_y ? 1 : -1;

        if(origin.y + step_y > -1 && origin.y + step_y < 8) {
            if(dynamic_cast<King *>(board[origin.x][origin.y + step_y]))
                if(board[origin.x][origin.y + step_y]->getis_white() == getis_white())
                origin.y += step_y;
        }

        vector<coordinates> moves = getvertical_moves(origin, direction_y, board);
        if(moves.empty())
            return false;

        coordinates position = moves.back();
        if(dynamic_cast<Rook *>(board[position.x][position.y]) || dynamic_cast<Queen *>(board[position.x][position.y]))
            return true;
        
        if(moves.size() == 1) {
            if(dynamic_cast<King *>(board[position.x][position.y]))
                return true;
        }

        return false;
    }

    bool is_checked_L(const coordinates &origin, const vector<vector<Piece *>> &board) {
        vector<coordinates> moves = getL_moves(origin, board);
        if(moves.empty())
            return false;

        for(auto position: moves) {
            if(dynamic_cast<Knight *>(board[position.x][position.y]))
                return true;
        }

        return false;
    }

};

#endif // KING.H
