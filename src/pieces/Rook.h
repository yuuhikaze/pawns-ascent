#ifndef ROOK_H
#define ROOK_H

#include "Piece.h"
using namespace std;

class Rook : public Piece {
  public:
    Rook(char symbol, bool is_white) : Piece(symbol, is_white) {}

    bool is_movement_valid(int origin_x, int origin_y, int target_x, int target_y) const override {
        /* TODO: Implementar validaci�n de movimiento de la Torre
           (Por ejemplo, movimiendo a los lados y adelante o atras) */
        return true; // Temporal: Permitir todos los movimientos para la prueba
    }
};

#endif //ROOK.H