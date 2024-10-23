#ifndef BISHOP_H
#define BISHOP_H

#include "Piece.h"
using namespace std;

class Bishop : public Piece {
  public:
    Bishop(char symbol, bool is_white) : Piece(symbol, is_white) {}

    bool is_movement_valid(int origin_x, int origin_y, int target_x, int target_y) const override {
        // TODO: Implementar validaci�n de movimiento del alfil
        // (Por ejemplo, movimientos diagonales)
        return true; // Temporal: Permitir todos los movimientos para la prueba
    }
};

#endif //BISHOP.H