#include "game_state.h"
#include "piece.h"

bool GameState::will_promote = false;

bool GameState::will_en_passant = false;
coordinates GameState::en_passant_capture = coordinates(-1, -1);
coordinates GameState::en_passant_target = coordinates(-1, -1);

bool GameState::will_castle = false;
bool GameState::is_short_castle = false;

coordinates GameState::white_king = coordinates(-1, -1);
coordinates GameState::black_king = coordinates(-1, -1);

bool GameState::is_checkmated_white = false;
bool GameState::is_checkmated_black = false;
bool GameState::is_stalemate = false;
bool GameState::is_insufficient_material = false;
