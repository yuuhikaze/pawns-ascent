#ifndef BOARD_H
#define BOARD_H

#include <unordered_map>
#include "pieces/bishop.h"
#include "pieces/king.h"
#include "pieces/knight.h"
#include "pieces/pawn.h"
#include "pieces/queen.h"
#include "pieces/rook.h"
#include "game_state.h"

using namespace std;

class Board {

  public:
    Board() { initialize_board(); }

    void initialize_board() {

        board.resize(8, vector<Piece *>(8, nullptr));

        // add_piece('r', coordinates(0, 7), false);
        // add_piece('r', coordinates(7, 7), false);

        // add_piece('n', coordinates(1, 7), false);
        // add_piece('n', coordinates(6, 7), false);

        // add_piece('b', coordinates(2, 7), false);
        // add_piece('b', coordinates(5, 7), false);

        // add_piece('q', coordinates(3, 7), false);
        // add_piece('k', coordinates(4, 7), false);

        // for(int column = 0; column < 8; column++) {
        //     add_piece('p', coordinates(column, 6), false);
        // }

        // add_piece('r', coordinates(0, 0), true);
        // add_piece('r', coordinates(7, 0), true);

        // add_piece('n', coordinates(1, 0), true);
        // add_piece('n', coordinates(6, 0), true);

        // add_piece('b', coordinates(2, 0), true);
        // add_piece('b', coordinates(5, 0), true);

        // add_piece('q', coordinates(3, 0), true);
        // add_piece('k', coordinates(4, 0), true);

        // for(int column = 0; column < 8; column++) {
        //     add_piece('p', coordinates(column, 1), true);
        // }


        add_piece('k', coordinates(4, 0), true);
        add_piece('r', coordinates(2, 0), true);
        add_piece('b', coordinates(0, 2), true);
        add_piece('p', coordinates(6, 5), true);
        
        add_piece('k', coordinates(6, 7), false);
        add_piece('p', coordinates(0, 6), false);
        add_piece('p', coordinates(1, 6), false);
        add_piece('p', coordinates(5, 6), false);
        add_piece('p', coordinates(6, 6), false);
        add_piece('p', coordinates(7, 6), false);
        add_piece('r', coordinates(0, 5), false);
        add_piece('n', coordinates(5, 4), false);
    }

    void display_board() const {
        // Mostrar el encabezado del tablero (letra columna)
        cout << endl
             << "\ta b c d e f g h" << endl
             << endl;

        for (int row = 7; row >= 0; row--) {
            cout << row + 1 << "\t"; // Numero de fila

            for (int column = 0; column < 8; column++) {
                Piece *piece = board[column][row];

                if (piece) {
                    char symbol = piece->getsymbol();
                    cout << symbol << " ";
                } else {
                    cout << ". "; // Casilla vacia
                }
            }

            cout << "\t" << row + 1 << endl; // Numero de fila
        }

        // Mostrar el encabezado del tablero (letra columna)
        cout << endl
             << "\ta b c d e f g h" << endl
             << endl;
    }

    bool move(const string &origin_string, const string &target_string, const bool &is_white_turn) {
        if (origin_string == target_string) {
            cout << "Same origin and target" << endl;
            return false;
        }
        
        vector<int> move = map_position_to_coordinates(origin_string, target_string);

        for (auto i : move) {
            if (i < 0 || i > 7) {
                // Testing message. Please remove later
                cout << "Out of bounds. Please enter valid coordinates" << endl;
                return false;
            }
        }

        coordinates origin(move[0], move[1]);
        coordinates target(move[2], move[3]);

        if (board[origin.x][origin.y] == nullptr) {
            // Testing message. Please remove later
            cout << "Origin is empty. There must be a piece on the origin" << endl;
            return false;
        }

        if (board[origin.x][origin.y]->getis_white() != is_white_turn) {
            // Testing message. Please remove later
            cout << "Please move the correct color piece" << endl;
            return false;
        }

        if (board[origin.x][origin.y]->is_movement_valid(origin, target, board)) {            
            
            Piece* temp = board[target.x][target.y];
            board[target.x][target.y] = board[origin.x][origin.y];
            board[origin.x][origin.y] = nullptr;

            if(GameState::will_castle) {
                if(GameState::is_short_castle) {
                    board[5][origin.y] = board[7][origin.y];
                    board[7][origin.y] = nullptr;
                    update_pieces_map(coordinates(7, origin.y), coordinates(5, origin.y), is_white_turn);
                    GameState::will_castle = false;
                    // print_current_pieces();
                    return true;
                }

                else {
                    board[3][origin.y] = board[0][origin.y];
                    board[0][origin.y] = nullptr;
                    update_pieces_map(coordinates(0, origin.y), coordinates(3, origin.y), is_white_turn);
                    GameState::will_castle = false;
                    // print_current_pieces();
                    return true;
                }
            }

            bool is_checked;
            if (is_white_turn)
                is_checked = board[GameState::white_king.x][GameState::white_king.y]->is_checked(GameState::white_king, board);
            else
                is_checked = board[GameState::black_king.x][GameState::black_king.y]->is_checked(GameState::black_king, board);
            
            if (is_checked) { 
                board[origin.x][origin.y] = board[target.x][target.y];
                board[target.x][target.y] = temp;
                GameState::will_en_passant = false;
                GameState::will_promote = false;
                // Testing message. Please remove later
                cout << "That move puts you into check (dickhead)" << endl;
                return false; 
            }

            update_pieces_map(origin, target, is_white_turn);

            if(temp != nullptr) {
                delete temp;
                temp = nullptr;
                if(is_white_turn)
                    black_pieces.erase(target);
                else
                    white_pieces.erase(target);
            }

            // cout << "Possible moves: " << endl;
            // vector<coordinates> moves = board[target.x][target.y]->getmoves(target, board);
            // for(auto i: moves) {
            //             cout << "x: " << i.x << "  y: " << i.y << endl;
            // }

            if (GameState::will_promote) {
                promote(target);
                GameState::will_promote = false;
            }

            else if(GameState::will_en_passant) {
                delete board[GameState::en_passant_target.x][GameState::en_passant_target.y];
                board[GameState::en_passant_target.x][GameState::en_passant_target.y] = nullptr;
                if(is_white_turn)
                    black_pieces.erase(GameState::en_passant_target);
                else
                    white_pieces.erase(GameState::en_passant_target);
                GameState::en_passant_target = coordinates(-1, -1);
                GameState::en_passant_capture = coordinates(-1, -1);
                GameState::will_en_passant = false;
            }

            if(is_white_turn) {
                if(board[GameState::black_king.x][GameState::black_king.y]->is_checked(GameState::black_king, board))
                    check_checkmate(!is_white_turn);
                else if(!can_king_move(!is_white_turn))
                    check_stalemate(!is_white_turn);
            }
            else {
                if(board[GameState::white_king.x][GameState::white_king.y]->is_checked(GameState::white_king, board))
                    check_checkmate(!is_white_turn);
                else if(!can_king_move(!is_white_turn))
                    check_stalemate(!is_white_turn);
            }

            // print_current_pieces();
            return true;
        }

        else {
            // Testing message. Please remove later
            cout << "Illegal move. Please make a valid move with the " << board[origin.x][origin.y]->getsymbol() << endl;
            return false;
        }
    }

    void clear_board() {
        // Deletes all allocated memory space and sets null pointers
        for (int columns = 0; columns < 8; columns++) {
            for (int rows = 0; rows < 8; rows++) {
                delete board[columns][rows];
                board[columns][rows] = nullptr;
            }
        }
    }

  private:
    vector<vector<Piece *>> board;
    unordered_map<coordinates, char> white_pieces;
    unordered_map<coordinates, char> black_pieces;

    vector<int> map_position_to_coordinates(const string &origin, const string &target) const {
        map<string, int> board_positions = {{"a", 0}, {"b", 1}, {"c", 2}, {"d", 3}, {"e", 4}, {"f", 5}, {"g", 6}, {"h", 7}};
        vector<int> coordinates;

        // checks for valid position
        if (board_positions.find(origin.substr(0, 1)) == board_positions.end()) {
            cerr << "Invalid column letter in origin: " << origin << endl;
            return {-1};
        }  

        if (board_positions.find(target.substr(0, 1)) == board_positions.end()) {
            cerr << "Invalid column letter in target: " << target << endl;
            return {-1};
        }
        
        int origin_x = board_positions[origin.substr(0, 1)];
        int origin_y = stoi(origin.substr(1, 1)) - 1;

        coordinates.push_back(origin_x);
        coordinates.push_back(origin_y);

        int target_x = board_positions[target.substr(0, 1)];
        int target_y = stoi(target.substr(1, 1)) - 1;

        coordinates.push_back(target_x);
        coordinates.push_back(target_y);

        return coordinates; // coordinates = [origin_x, origin_y, target_x,
                            // target_y]
    }

    void promote(const coordinates &target) {
        int menu;
        bool is_white = board[target.x][target.y]->getis_white();
        delete board[target.x][target.y];
        board[target.x][target.y] = nullptr;

        cout << "Your pawn can promote! Choose and option: " << endl;
        do {
            cout << "1.) Queen" << endl
                 << "2.) Rook" << endl
                 << "3.) Bishop" << endl
                 << "4.) Knight" << endl;

            cin >> menu;

            if (menu == 1)
                board[target.x][target.y] = new Queen(is_white);

            else if (menu == 2)
                board[target.x][target.y] = new Rook(is_white);

            else if (menu == 3)
                board[target.x][target.y] = new Bishop(is_white);

            else if (menu == 4)
                board[target.x][target.y] = new Knight(is_white);

            else
                cout << "Invalid option. Please select a valid option" << endl;

        } while (menu < 1 || menu > 4);

        if(is_white)
            white_pieces[target] = board[target.x][target.y]->getsymbol();
        else
            black_pieces[target] = board[target.x][target.y]->getsymbol();
        cout << "\033[2J\033[1;1H";
    }

    void add_piece(const char &symbol, const coordinates &postion, const bool &is_white) {
        if(board[postion.x][postion.y] != nullptr) {
            cout << "There is already a piece at that position" << endl;
            return;
        }
        
        switch(tolower(symbol)) {
            case 'p':
                board[postion.x][postion.y] = new Pawn(is_white);
                break;

            case 'b':
                board[postion.x][postion.y] = new Bishop(is_white);
                break;
            
            case 'n':
                board[postion.x][postion.y] = new Knight(is_white);
                break;
            
            case 'r':
                board[postion.x][postion.y] = new Rook(is_white);
                break;                  
            
            case 'q':
                board[postion.x][postion.y] = new Queen(is_white);
                break;

            case 'k':
                board[postion.x][postion.y] = new King(is_white);
                if(is_white)
                    GameState::white_king = postion;
                else
                    GameState::black_king = postion;
                return;
            
            default:
                cerr << "ERROR: provided symbol doesn't match any piece type" << endl;    
        }

        if(is_white)
            white_pieces[postion] = tolower(symbol);
        else
            black_pieces[postion] = toupper(symbol);
    }

    // AFTER a move on the board is complete, updates the map that keeps track of the pieces
    void update_pieces_map(const coordinates &origin, const coordinates target, const bool &is_white) {
        if(tolower(board[target.x][target.y]->getsymbol()) == 'k' )
            return;

        if(is_white) {
            white_pieces[target] = board[target.x][target.y]->getsymbol();
            white_pieces.erase(origin);
        }
        else {
            black_pieces[target] = board[target.x][target.y]->getsymbol();
            black_pieces.erase(origin);
        }
    }

    // Prints a list of all the pieces in the game. For debugging purposes
    void print_current_pieces() const {
        cout << "White Pieces: " << endl << endl;
        cout << "King: (" << GameState::white_king.x << ", " << GameState::white_king.y << ")" << endl;
        for(const auto& piece : white_pieces) {
            cout << piece.second << ": (" << piece.first.x << ", " << piece.first.y << ")" << endl;
        }

        cout << endl << "Black Pieces: " << endl << endl;
        cout << "King: (" << GameState::black_king.x << ", " << GameState::black_king.y << ")" << endl;
        for(const auto& piece : black_pieces) {
            cout << piece.second << ": (" << piece.first.x << ", " << piece.first.y << ")" << endl;
        }
        cout << endl;
    }

    // Verifies if the king has at least one spot to which it can move
    bool can_king_move(const bool &is_white) const {
        coordinates origin;
        if(is_white)
            origin = GameState::white_king;
        else
            origin = GameState::black_king;

        if(origin.y < 7) {
            for(int i = origin.x - 1; i < origin.x + 2; i++) {
                if(board[origin.x][origin.y]->is_valid_tile(coordinates(i, origin.y + 1), board))
                    if(!board[origin.x][origin.y]->is_checked(coordinates(i, origin.y + 1), board))
                        return true;
            }
        }

        if(origin.y > 0) {
            for(int i = origin.x - 1; i < origin.x + 2; i++) {
                if(board[origin.x][origin.y]->is_valid_tile(coordinates(i, origin.y - 1), board))
                    if(!board[origin.x][origin.y]->is_checked(coordinates(i, origin.y - 1), board))
                        return true;
            }
        }

        if(board[origin.x][origin.y]->is_valid_tile(coordinates(origin.x - 1, origin.y), board)) {
            if(!board[origin.x][origin.y]->is_checked(coordinates(origin.x - 1, origin.y), board))
                return true;
        }

        if(board[origin.x][origin.y]->is_valid_tile(coordinates(origin.x + 1, origin.y), board)) {
            if(!board[origin.x][origin.y]->is_checked(coordinates(origin.x + 1, origin.y), board))
                return true;
        }

        return false;
    }

    // Attempts to find a legal move for the specified color
    // Returns true if it finds a legal move. Else, return false
    bool find_legal_move(const bool &is_white) {
        if(can_king_move(is_white))
            return true;

        if(is_white) {
            for(const auto& piece : white_pieces) {
                vector<coordinates>total_moves = board[piece.first.x][piece.first.y]->getmoves(piece.first, board);
                // cout << "Possible moves: " << endl;
                // for(auto i: total_moves) {
                //     cout << "(" << i.x << ", " << i.y << ")  ";
                // }
                // cout << endl;

                coordinates prev_position = piece.first;
                Piece* temp  = nullptr;
                // cout << "Piece currently being checked: " << piece.second << ": (" << piece.first.x << ", " << piece.first.y << ")" << endl << endl;
                
                for(const auto &position : total_moves) {               
                    temp = board[position.x][position.y];
                    board[position.x][position.y] = board[prev_position.x][prev_position.y];
                    board[prev_position.x][prev_position.y] = nullptr;

                    // cout << "Prev Postition: " << ": (" << prev_position.x << ", " << prev_position.y << ")" << endl;
                    // cout << "Current Postition: " << ": (" << position.x << ", " << position.y << ")" << endl;
                    // display_board()

                    if(!board[GameState::white_king.x][GameState::white_king.y]->is_checked(GameState::white_king, board)) {
                        board[piece.first.x][piece.first.y] = board[position.x][position.y];
                        board[position.x][position.y] = temp;
                        return true;
                    }

                    if(temp != nullptr) {
                        board[prev_position.x][prev_position.y] = board[position.x][position.y];
                        board[position.x][position.y] = temp;
                        continue;
                    }
                    else
                        prev_position = position; 
                }

                if(piece.first != prev_position) {
                    board[piece.first.x][piece.first.y] = board[prev_position.x][prev_position.y];
                    board[prev_position.x][prev_position.y] = nullptr;
                }
                // display_board();
            }
        }

        else {
            for(const auto& piece : black_pieces) {
                vector<coordinates>total_moves = board[piece.first.x][piece.first.y]->getmoves(piece.first, board);
                // cout << "Possible moves: " << endl;
                // for(auto i: total_moves) {
                //     cout << "(" << i.x << ", " << i.y << ")  ";
                // }
                // cout << endl;
                
                coordinates prev_position = piece.first;
                Piece* temp  = nullptr;
                // cout << "Piece currently being checked: " << piece.second << ": (" << piece.first.x << ", " << piece.first.y << ")" << endl << endl;

                for(const auto &position : total_moves) {               
                    temp = board[position.x][position.y];
                    board[position.x][position.y] = board[prev_position.x][prev_position.y];
                    board[prev_position.x][prev_position.y] = nullptr;

                    // cout << "Prev Postition: " << ": (" << prev_position.x << ", " << prev_position.y << ")" << endl;
                    // cout << "Current Postition: " << ": (" << position.x << ", " << position.y << ")" << endl;
                    // display_board();

                    if(!board[GameState::black_king.x][GameState::black_king.y]->is_checked(GameState::black_king, board)) {
                        board[piece.first.x][piece.first.y] = board[position.x][position.y];
                        board[position.x][position.y] = temp;
                        return true;
                    }

                    if(temp != nullptr) {
                        board[prev_position.x][prev_position.y] = board[position.x][position.y];
                        board[position.x][position.y] = temp;
                        continue;
                    }
                    else
                        prev_position = position;  
                }

                if(piece.first != prev_position) {
                    board[piece.first.x][piece.first.y] = board[prev_position.x][prev_position.y];
                    board[prev_position.x][prev_position.y] = nullptr;
                }
                // display_board();
            }         
        }
        return false;
    }

    void check_checkmate(const bool &is_white) {
        cout << "Checking chekmate..." << endl;
        if(!find_legal_move(is_white)) {
            if(is_white) {
                cout << "Checkmate!" << endl << endl;
                GameState::is_checkmated_white = true;
                return;
            }
            else {
                cout << "Checkmate!" << endl << endl;
                GameState::is_checkmated_black = true;
                return;
            }
        }
        else
            cout << "No checkmate" << endl << endl;
    }

    void check_stalemate(const bool &is_white) {
        cout << "Checking stalemate..." << endl;
        if(!find_legal_move(is_white)) {
            cout << "Stalemate..." << endl << endl;
            GameState::is_stalemate = true;
        }
        else
            cout << "No stalemate" << endl << endl;
    }
};

#endif // BOARD_H
