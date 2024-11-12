#ifndef PIECE_H
#define PIECE_H

#include <iostream>
#include <map>
#include <string>
#include <vector>

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

class Piece {
  private:
    char symbol;
    bool is_white;

  public:
    Piece(char symbol, bool is_white) {
        this->is_white = is_white;

        if (is_white)
            this->symbol = (char)tolower(symbol);
        else
            this->symbol = (char)toupper(symbol);
    }
    virtual ~Piece() {}

    virtual bool is_movement_valid(coordinates origin, coordinates target, const vector<vector<Piece *>> &board) = 0;
    
    virtual std::vector<coordinates> getmoves(coordinates origin, const vector<vector<Piece *>> &board) = 0;

    char getsymbol() const { return symbol; }
    bool getis_white() const { return is_white; }

 protected:

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

    // Helper function used to calculate the displacement of a given move
    std::vector<int> calc_displacement(const coordinates &origin, coordinates const &target) const {
        int delta_x = target.x - origin.x;
        int delta_y = target.y - origin.y;
        return {delta_x, delta_y};
    }

    // Helper function used to get all possible moves of a specified diagonal from a given origin
    // For direction_x, true => right, false => left
    // For direction_y, true => up, false => down 
    vector<coordinates> getdiagonal_moves(const coordinates &origin, const bool direction_x, const bool direction_y, const vector<vector<Piece *>> &board) const {
        int step_x = direction_x ? 1 : -1;
        int step_y = direction_y ? 1 : -1;
        
        int i = origin.x + step_x;
        int j = origin.y + step_y;

        vector<coordinates> moves;

        while (i < 8 && i > -1 && j < 8 && j > -1) {
            if (board[i][j] != nullptr) {
                if(is_valid_tile(coordinates(i, j), board)) {
                    moves.push_back(coordinates(i, j));
                    return moves;
                }  

                else
                    return moves;
            }

            moves.push_back(coordinates(i, j));
            i += step_x;
            j += step_y;
        }

        return moves;
    }

    // Helper function used to get all possible horizontal moves from a given position
    // For direction_x, true => right, false => left
    vector<coordinates> gethorizontal_moves(const coordinates &origin, const bool direction_x, const vector<vector<Piece *>> &board) const {
        int step = direction_x ? 1 : -1;
        int i = origin.x + step;
        
        vector<coordinates> moves;

        while (i < 8 && i > -1) {
            if (board[i][origin.y] != nullptr) {
                if(is_valid_tile(coordinates(i, origin.y), board)) {
                    moves.push_back(coordinates(i, origin.y));
                    return moves;
                }

                else 
                    return moves;
            }

            moves.push_back(coordinates(i, origin.y));
            i += step;
        }

        return moves;
    }

    // Helper function used to get all possible vertical moves from a given position
    // For direction_y, true => up, false => down 
    vector<coordinates> getvertical_moves(const coordinates &origin, const bool direction_y, const vector<vector<Piece *>> &board) const {
        int step = direction_y ? 1 : -1;
        int j = origin.y + step;
        
        vector<coordinates> moves;

        while (j < 8 && j > -1) {
            if (board[origin.x][j] != nullptr) {
                if(is_valid_tile(coordinates(origin.x, j), board)) {
                    moves.push_back(coordinates(origin.x, j));
                    break;
                }

                else 
                    break; 
            }

            moves.push_back(coordinates(origin.x, j));
            j += step;
        }

        return moves;
    }

    // Helper function used to get all possible L moves from a given position
    vector<coordinates> getL_moves (const coordinates &origin, const vector<vector<Piece *>> &board) const {
        vector<coordinates> moves;

        if(is_valid_tile(coordinates(origin.x + 2, origin.y + 1), board))
            moves.push_back(coordinates(origin.x + 2, origin.y + 1));
        
        if(is_valid_tile(coordinates(origin.x + 1, origin.y + 2), board))
            moves.push_back(coordinates(origin.x + 1, origin.y + 2));
        
        if(is_valid_tile(coordinates(origin.x - 1, origin.y + 2), board))
            moves.push_back(coordinates(origin.x - 1, origin.y + 2));
        
        if(is_valid_tile(coordinates(origin.x - 2, origin.y + 1), board))
            moves.push_back(coordinates(origin.x - 2, origin.y + 1));
        
        if(is_valid_tile(coordinates(origin.x - 2, origin.y - 1), board))
            moves.push_back(coordinates(origin.x - 2, origin.y - 1));
        
        if(is_valid_tile(coordinates(origin.x - 1, origin.y - 2), board))
            moves.push_back(coordinates(origin.x - 1, origin.y - 2));
        
        if(is_valid_tile(coordinates(origin.x + 1, origin.y - 2), board))
            moves.push_back(coordinates(origin.x + 1, origin.y - 2));
        
        if(is_valid_tile(coordinates(origin.x + 2, origin.y - 1), board))
            moves.push_back(coordinates(origin.x + 2, origin.y - 1));

        return moves;
    }

};

#endif // PIECE.H
