#ifndef PAWN_H
#define PAWN_H

#include "../piece.h"
using namespace std;

class Pawn : public Piece {
  public:
    Pawn(bool is_white) : Piece('p', is_white) { has_moved = false; }

    bool is_movement_valid(coordinates origin, coordinates target, const vector<vector<Piece *>> &board) override {

        vector<int> displacement = calc_displacement(origin, target);
        int delta_x = displacement[0];
        int delta_y = displacement[1];

        if ((getis_white() && delta_y < 0) || (!getis_white() && delta_y > 0)) {
            cout << "Backwards pawn move" << endl;
            return false;
        }

        if (delta_x == 0 && abs(delta_y) < 3) {
            int step = delta_y < 0 ? -1 : 1;

            if (abs(delta_y) == 2 && !has_moved) {
                if (board[origin.x][origin.y + step] != nullptr)
                    return false;
                if (board[origin.x][origin.y + 2 * step] != nullptr)
                    return false;
                else {
                    has_moved = true;
                    GameState::en_passant_capture = coordinates(origin.x, origin.y + step);
                    GameState::en_passant_target = coordinates(target.x, target.y);
                    return true;
                }
            }

            if (abs(delta_y) == 1) {
                if (board[origin.x][origin.y + step] != nullptr)
                    return false;
                else {
                    if(!has_moved)
                        has_moved = true;
                    set_default_en_passant();
                    if(target.y == 7 || target.y == 0)
                        GameState::will_promote = true;
                    return true;
                }
            }

            else {
                return false;
            }
        }

        if (abs(delta_y) == 1 && abs(delta_x) == 1) {
            if(target == GameState::en_passant_capture) {
                GameState::will_en_passant = true;
                return true;
            }
            if (board[target.x][target.y] == nullptr)
                return false;
            if (board[target.x][target.y]->getis_white() == getis_white())
                return false;
            else {
                if(!has_moved)    
                    has_moved = true;
                set_default_en_passant();
                if(target.y == 7 || target.y == 0)
                    GameState::will_promote = true;
                return true;
            }
        }

        else
            return false;
    }

    vector<coordinates> getmoves(coordinates origin, const vector<vector<Piece *>> &board) override {
        vector<coordinates> moves;

        if(getis_white()) {
            if(origin.y < 7) {
                if(board[origin.x][origin.y + 1] == nullptr)
                    moves.push_back(coordinates(origin.x, origin.y + 1));
            }
            
            if(origin.y < 6) {
                if(!has_moved && board[origin.x][origin.y + 2] == nullptr)
                    moves.push_back(coordinates(origin.x, origin.y + 2));
            }

            if(origin.x < 7) {
                if(board[origin.x + 1][origin.y + 1] != nullptr) {
                    if(board[origin.x + 1][origin.y + 1]->getis_white() != getis_white())
                        moves.push_back(coordinates(origin.x + 1, origin.y + 1));
                }
            }

            if(origin.x > 0) {
                if(board[origin.x - 1][origin.y + 1] != nullptr) {
                    if(board[origin.x - 1][origin.y + 1]->getis_white() != getis_white())
                        moves.push_back(coordinates(origin.x - 1, origin.y + 1));
                }
            }
        }

        else {
            if(origin.y > 0) {
                if(board[origin.x][origin.y - 1] == nullptr)
                    moves.push_back(coordinates(origin.x, origin.y + 1));
            }
            
            if(origin.y > 1) {
                if(!has_moved && board[origin.x][origin.y - 2] == nullptr)
                    moves.push_back(coordinates(origin.x, origin.y + 2));
            }

            if(origin.x < 7) {
                if(board[origin.x + 1][origin.y - 1] != nullptr) {
                    if(board[origin.x + 1][origin.y - 1]->getis_white() != getis_white())
                        moves.push_back(coordinates(origin.x + 1, origin.y - 1));
                }
            }

            if(origin.x > 0) {
                if(board[origin.x - 1][origin.y - 1] != nullptr) {
                    if(board[origin.x - 1][origin.y - 1]->getis_white() != getis_white())
                        moves.push_back(coordinates(origin.x - 1, origin.y - 1));
                }
            }
        }
        
        return moves;
    }

  private:
    bool has_moved;
};

#endif // PAWN.H
