#ifndef PIECE_H
#define PIECE_H

#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

struct coordinates {   
    coordinates(int x, int y) {
        this->x = x;
        this->y = y;
    }

    int x;
    int y;
};

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

    virtual bool is_movement_valid(coordinates origin, coordinates target, const vector<vector<Piece *>> &board) = 0;

    std::vector<int> calc_displacement(coordinates origin, coordinates target) const {
        //Calculates the displacement of a given movement. Used for some movement logic
        int delta_x = target.x - origin.x;
        int delta_y = target.y - origin.y;
        return {delta_x, delta_y};
    }

    char getsymbol() const { return symbol; }
    bool getis_white() const { return is_white; }
};


#endif //PIECE.H