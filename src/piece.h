#ifndef PIECE_H
#define PIECE_H

#include <iostream>
#include <map>
#include <string>
#include <vector>
#include "game_state.h"

using namespace std;

struct coordinates {
    coordinates(int x, int y) {
        this->x = x;
        this->y = y;
    }

    coordinates() {
        x = 0;
        y = 0;
    }

    bool operator!= (const coordinates &other) const {
        return x != other.x || y != other.y;
    }

    bool operator== (const coordinates &other) const {
        return x == other.x && y == other.y;
    }

    int x;
    int y;
};

namespace std {
    template <>
    struct hash<coordinates> {
        std::size_t operator()(const coordinates& coord) const {
            return std::hash<int>()(coord.x) ^ (std::hash<int>()(coord.y) << 1);
        }
    };
}

class Piece {
  public:
    bool has_moved;

    Piece(char symbol, bool is_white) {
        this->is_white = is_white;
        has_moved = false;
        if (is_white)
            this->symbol = (char)tolower(symbol);
        else
            this->symbol = (char)toupper(symbol);
    }
    virtual ~Piece() {}

    virtual bool is_movement_valid(coordinates origin, coordinates target, const vector<vector<Piece *>> &board) = 0;
    
    virtual vector<coordinates> getmoves(coordinates origin, const vector<vector<Piece *>> &board) = 0;

    char getsymbol() const { return symbol; }
    bool getis_white() const { return is_white; }
    bool gethas_moved() const {return has_moved;}

    // Determines if a piece is currently checked in the target coordinates
    bool is_checked(const coordinates &target, const vector<vector<Piece *>> &board) {
        
        if(is_checked_diagonal(target, true, true, board))
            return true;
        
        if(is_checked_diagonal(target, true, false, board))
            return true;
        
        if(is_checked_diagonal(target, false, false, board))
            return true;
        
        if(is_checked_diagonal(target, false, true, board))
            return true;

        if(is_checked_horizontal(target, true, board))
            return true;
        
        if(is_checked_horizontal(target, false, board))
            return true;
        
        if(is_checked_vertical(target, true, board))
            return true;

        if(is_checked_vertical(target, false, board))
            return true;
        
        if(is_checked_L(target, board))
            return true;
        
        return false;
    }
    
    // Helper function to determine if the target position can be occupied by a piece
    bool is_valid_tile(coordinates const &target, const vector<vector<Piece *>> &board) const {
        if(target.x > 7 || target.x < 0 || target.y > 7 || target.y < 0)
            return false;
            
        if (board[target.x][target.y] != nullptr) {
            if(board[target.x][target.y]->getis_white() == getis_white())
                return false;
            else
                return true;            
            }
        return true;
    }    

  protected:

    // Helper function used to calculate the displacement of a given move
    std::vector<int> calc_displacement(const coordinates &origin, coordinates const &target) const {
        int delta_x = target.x - origin.x;
        int delta_y = target.y - origin.y;
        return {delta_x, delta_y};
    }

    // Helper function used to get the Line of Sight of a specified diagonal from a given origin
    // For direction_x, true => right, false => left
    // For direction_y, true => up, false => down 
    vector<coordinates> getdiagonal_LOS(const coordinates &origin, const bool direction_x, const bool direction_y, const vector<vector<Piece *>> &board) const {
        int step_x = direction_x ? 1 : -1;
        int step_y = direction_y ? 1 : -1;
        
        int i = origin.x + step_x;
        int j = origin.y + step_y;

        vector<coordinates> moves;

        while (i < 8 && i > -1 && j < 8 && j > -1) {
            if (board[i][j] != nullptr) {
                if(board[i][j] == this)
                    moves.push_back(coordinates(i, j));
                else {   
                    moves.push_back(coordinates(i, j));
                    return moves;
                }
            }
            moves.push_back(coordinates(i, j));
            i += step_x;
            j += step_y;
        }

        return moves;
    }

    // Helper function used to get the horizontal Line of Sight from a given position
    // For direction_x, true => right, false => left
    vector<coordinates> gethorizontal_LOS(const coordinates &origin, const bool direction_x, const vector<vector<Piece *>> &board) const {
        int step = direction_x ? 1 : -1;
        int i = origin.x + step;
        
        vector<coordinates> moves;

        while (i < 8 && i > -1) {
            if (board[i][origin.y] != nullptr) {
                if(board[i][origin.y] == this)
                    moves.push_back(coordinates(i, origin.y));
                else { 
                    moves.push_back(coordinates(i, origin.y));
                    return moves;
                }
            }
            moves.push_back(coordinates(i, origin.y));
            i += step;
        }

        return moves;
    }

    // Helper function used to get the vertical Line of Sight from a given position
    // For direction_y, true => up, false => down 
    vector<coordinates> getvertical_LOS(const coordinates &origin, const bool direction_y, const vector<vector<Piece *>> &board) const {
        int step = direction_y ? 1 : -1;
        int j = origin.y + step;
        
        vector<coordinates> moves;

        while (j < 8 && j > -1) {
            if (board[origin.x][j] != nullptr) {
                if(is_valid_tile(coordinates(origin.x, j), board)) {
                    moves.push_back(coordinates(origin.x, j));
                    return moves;
                }
                else if(board[origin.x][j] == this)
                    moves.push_back(coordinates(origin.x, j));
                else 
                    return moves; 
            }

            moves.push_back(coordinates(origin.x, j));
            j += step;
        }

        return moves;
    }

    // Helper function used to get L shaped Line of Sight moves from a given position
    vector<coordinates> getL_LOS (const coordinates &origin, const vector<vector<Piece *>> &board) const {
        vector<coordinates> moves;

        if(origin.x + 2 < 8 && origin.y + 1 < 8)
            moves.push_back(coordinates(origin.x + 2, origin.y + 1));
        
        if(origin.x + 1 < 8 && origin.y + 2 < 8)
            moves.push_back(coordinates(origin.x + 1, origin.y + 2));
        
        if(origin.x - 1 > -1 && origin.y + 2 < 8)
            moves.push_back(coordinates(origin.x - 1, origin.y + 2));
        
        if(origin.x - 2 > -1 && origin.y + 1 < 8)
            moves.push_back(coordinates(origin.x - 2, origin.y + 1));
        
        if(origin.x - 2 > -1 && origin.y - 1 > -1)
            moves.push_back(coordinates(origin.x - 2, origin.y - 1));
        
        if(origin.x - 1 > -1 && origin.y - 2 > -1)
            moves.push_back(coordinates(origin.x - 1, origin.y - 2));
        
        if(origin.x + 1 < 8 && origin.y - 2 > -1)
            moves.push_back(coordinates(origin.x + 1, origin.y - 2));
        
        if(origin.x + 2 < 8 && origin.y - 1 > -1)
            moves.push_back(coordinates(origin.x + 2, origin.y - 1));

        return moves;
    }

    // Resets the variables used to keep track of en passant conditions to their default values
    void set_default_en_passant() {
        if(GameState::en_passant_capture != coordinates(-1, -1))
            GameState::en_passant_capture = coordinates(-1, -1);
        if(GameState::en_passant_target != coordinates(-1, -1))
            GameState::en_passant_target = coordinates(-1, -1);
    }

    // Verifies if a type of piece is at at a given position on the board based on the specified symbol
    // Lowercase => white piece. Uppercase => black piece
    bool check_piece(const char &symbol, const coordinates &position, const vector<vector<Piece *>> &board) const {
        if (board[position.x][position.y] != nullptr) {
            if(board[position.x][position.y]->getsymbol() == symbol)
                return true;
        }
        return false;
    }

  private:
    char symbol;
    bool is_white;

    // Verifies if a piece is being checked from a given diagonal
    bool is_checked_diagonal(coordinates origin, bool direction_x, bool direction_y, const vector<vector<Piece *>> &board) const {
        int step_x = direction_x ? 1 : -1;
        int step_y = direction_y ? 1 : -1;

        vector<coordinates> moves = getdiagonal_LOS(origin, direction_x, direction_y, board);
        if(moves.empty())
            return false;
        
        char bishop = 'b';
        char queen = 'q';
        char king = 'k';

        if(getis_white()) {
            bishop = toupper(bishop);
            queen = toupper(queen);
            king = toupper(king);
        }

        coordinates position = moves.back();
        if(check_piece(bishop, position, board) || check_piece(queen, position, board))
            return true;
        
        if(moves.size() == 1) {
            if(check_piece(king, position, board))
                return true;
            
            if(getis_white()) {
                if(direction_y && check_piece('P', position, board))
                    return true;
            }

            else {
                if(!direction_y && check_piece('p', position, board))
                    return true;
            }
        }

        return false;
    }

    bool is_checked_horizontal(coordinates origin, bool direction_x, const vector<vector<Piece *>> &board) const {
        int step_x = direction_x ? 1 : -1;

        vector<coordinates> moves = gethorizontal_LOS(origin, direction_x, board);
        if(moves.empty())
            return false;

        char rook = 'r';
        char queen = 'q';
        char king = 'k';

        if(getis_white()) {
            rook = toupper(rook);
            queen = toupper(queen);
            king = toupper(king);
        }

        coordinates position = moves.back();
        if(check_piece(rook, position, board) || check_piece(queen, position, board))
            return true;
        
        if(moves.size() == 1) {
            if(check_piece(king, position, board))
                return true;
        }

        return false;
    }

    bool is_checked_vertical(coordinates origin, bool direction_y, const vector<vector<Piece *>> &board) const {
        int step_y = direction_y ? 1 : -1;

        // if(origin.y + step_y > -1 && origin.y + step_y < 8) {
        //     if(board[origin.x][origin.y + step_y] ==  this)
        //     origin.y += step_y;
        // }

        vector<coordinates> moves = getvertical_LOS(origin, direction_y, board);
        if(moves.empty())
            return false;
        
        char rook = 'r';
        char queen = 'q';
        char king = 'k';

        if(getis_white()) {
            rook = toupper(rook);
            queen = toupper(queen);
            king = toupper(king);
        }

        coordinates position = moves.back();
        if(check_piece(rook, position, board) || check_piece(queen, position, board))
            return true;
        
        if(moves.size() == 1) {
            if(check_piece(king, position, board))
                return true;
        }

        return false;
    }

    bool is_checked_L(const coordinates &origin, const vector<vector<Piece *>> &board) {
        vector<coordinates> moves = getL_LOS(origin, board);
        if(moves.empty())
            return false;
        
        char knight = 'n';
        if(getis_white())
            knight = toupper(knight);
        
        for(auto position: moves) {
            if(check_piece(knight, position, board))
                return true;
        }

        return false;
    }

};

#endif // PIECE.H
