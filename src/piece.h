#ifndef PIECE_H
#define PIECE_H

#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

class Piece {
private:
    char symbol;
    bool is_white;

public:
    Piece(char symbol, bool is_white) {
        this->is_white = is_white;

        if (is_white)
            this->symbol = (char)tolower(symbol);
        else
            this->symbol = (char)toupper(symbol);
    }
    virtual ~Piece() {}

    virtual bool is_movement_valid(int origin_x, int origin_y, int target_x, int target_y, const vector<vector<Piece *>> &board) = 0;

    std::vector<int> calc_displacement(int origin_x, int origin_y, int target_x, int target_y) const {
        //Calculates the displacement of a given movement. Used for some movement logic
        int delta_x = target_x - origin_x;
        int delta_y = target_y - origin_y;
        return {delta_x, delta_y};
    }

    char getsymbol() const { return symbol; }
    bool getis_white() const { return is_white; }
};

#endif //PIECE.H