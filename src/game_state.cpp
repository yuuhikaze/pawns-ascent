#include "game_state.h"
#include "piece.h"

bool GameState::will_promote = false;

bool GameState::will_en_passant = false;
coordinates GameState::en_passant_capture = coordinates(-1, -1);
coordinates GameState::en_passant_target = coordinates(-1, -1);

coordinates GameState::white_king = coordinates(-1, -1);
coordinates GameState::black_king = coordinates(-1, -1);
bool GameState::is_white_checked = false;
bool GameState::is_black_checked = false;
