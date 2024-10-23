#ifndef KNIGHT_H
#define KNIGHT_H

#include "Piece.h"
using namespace std;

class Knight : public Piece {
  public:
    Knight(char symbol, bool is_white) : Piece(symbol, is_white) {}

    bool is_movement_valid(int origin_x, int origin_y, int target_x, int target_y) const override {
        // TODO: Implementar validaci�n de movimiento del caballo
        // (Por ejemplo, movimientos en L)
        return true; // Temporal: Permitir todos los movimientos
    }
};

#endif //KNIGHT_H