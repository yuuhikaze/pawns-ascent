#ifndef PAWN_H
#define PAWN_H

#include "../piece.h"
using namespace std;

class Pawn : public Piece {
  public:
    Pawn(bool is_white) : Piece('p', is_white) { has_moved = false; }

    bool is_movement_valid(coordinates origin, coordinates target,
                           const vector<vector<Piece *>> &board) override {

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
                    return true;
                }
            }

            if (abs(delta_y) == 1) {
                if (board[origin.x][origin.y + step] != nullptr)
                    return false;
                return true;
            }

            return false;
        }

        if (abs(delta_y) == 1 && abs(delta_x) == 1) {
            if (board[target.x][target.y] == nullptr)
                return false;
            if (board[target.x][target.y]->getis_white() == getis_white())
                return false;
            if (target.y == 7) {
            }
            return true;

        }

        else
            return false;
    }

  private:
    bool has_moved;
};

#endif // PAWN.H
