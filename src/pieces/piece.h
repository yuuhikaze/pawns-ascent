#ifndef PIECE_H
#define PIECE_H

#include <iostream>
#include <map>
#include <string>
#include <vector>

class Board;

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

    virtual bool is_movement_valid(int origin_x, int origin_y, int target_x, int target_y, Board &board) const = 0;

    char getsymbol() const { return symbol; }
    bool getis_white() const { return is_white; }
};

#endif //PIECE.H