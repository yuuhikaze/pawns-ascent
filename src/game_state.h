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

    static coordinates white_king;
    static coordinates black_king;
    static bool is_white_checked;
    static bool is_black_checked;
};

#endif // GAMESTATE_H