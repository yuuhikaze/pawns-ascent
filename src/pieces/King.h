#ifndef KING_H
#define KING_H

#include "Piece.h"
using namespace std;

class King : public Piece {
  public:
    King(char symbol, bool is_white) : Piece(symbol, is_white) {}

    bool is_movement_valid(int origin_x, int origin_y, int target_x, int target_y) const override {
        // TODO: Implementar validaci�n de movimiento del Rey
        // (Por ejemplo, avanzar una casilla en cualquier direccion)
        return true; // Temporal: Permitir todos los movimientos
    }
};

#endif //KING.H
