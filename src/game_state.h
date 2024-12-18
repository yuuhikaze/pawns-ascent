#ifndef GAMESTATE_H
#define GAMESTATE_H

using namespace std;

struct coordinates;

class GameState {
  public:
    static bool will_promote;

    static bool will_en_passant;
    static coordinates en_passant_capture;
    static coordinates en_passant_target;

    static bool will_castle;
    static bool is_short_castle;

    static coordinates white_king;
    static coordinates black_king;

    static bool is_checkmated_white;
    static bool is_checkmated_black;
    static bool is_stalemate;
    static bool is_insufficient_material;
};

#endif // GAMESTATE_H