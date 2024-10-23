#ifndef QUEEN_H
#define QUEEN_H

#include "Piece.h"
using namespace std;

class Queen : public Piece {
  public:
    Queen(char symbol, bool is_white) : Piece(symbol, is_white) {}

    bool is_movement_valid(int origin_x, int origin_y, int target_x, int target_y) const override {
        // TODO: Implementar validaci�n de movimiento de la Dama/Reina
        // (Por ejemplo, movimientos diagonales, adelante y atras e izquierda y
        // derecha)
        return true; // Temporal: Permitir todos los movimientos
    }
};

#endif //QUEEN.H