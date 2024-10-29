#ifndef BOARD_H
#define BOARD_H

#include "pieces/bishop.h"
#include "pieces/king.h"
#include "pieces/pawn.h"
#include "pieces/queen.h"
#include "pieces/rook.h"

using namespace std;

class Board {
  private:
    vector<vector<Piece *>> board;

  public:
    Board() { initialize_board(); }

    void initialize_board() {
    
        board.resize(8, std::vector<Piece *>(8, nullptr));

        for(int column = 0; column < 8; column++) {
            board[column][0] = new Bishop(true);
        }
    }


    void display_board() const {
        // Mostrar el encabezado del tablero (letra columna)
        cout << endl << "\ta b c d e f g h" << endl << endl;

        for (int row = 7; row >= 0; row--) {
            cout << row + 1 << "\t"; // N�mero de fila

            for (int column = 0; column < 8; column++) {
                Piece *piece = board[column][row];

                if (piece) {
                    char symbol = piece->getsymbol();
                    cout << symbol << " ";
                } else {
                    cout << ". "; // Casilla vac�a
                }
            }

            cout << "\t" << row + 1 << endl; // N�mero de fila
        }

        // Mostrar el encabezado del tablero (letra columna)
        cout << endl << "\ta b c d e f g h" << endl << endl;
    }

    vector<int> map_position_to_coordinates(string origin, string target) {
        /* Recibe el input del usuario (ejemplo: "b2", "b3") y
        lo traduce a coordinates X y Y. */
        map<string, int> board_positions = {{"a", 0}, {"b", 1}, {"c", 2}, {"d", 3}, {"e", 4}, {"f", 5}, {"g", 6}, {"h", 7}};
        vector<int> coordinates;

        if (board_positions.find(origin.substr(0, 1)) == board_positions.end()) {
            cerr << "Invalid column letter in origin: " << origin << endl;
            return {-1};
        }

        else{
        int origin_x = board_positions[origin.substr(0, 1)];
        int origin_y = stoi(origin.substr(1, 1)) - 1;
   
        coordinates.push_back(origin_x);
        coordinates.push_back(origin_y);
  ;
        }

        if (board_positions.find(target.substr(0, 1)) == board_positions.end()) {
            cerr << "Invalid column letter in target: " << target << endl;
            return{-1};
        }

        else{
            int target_x = board_positions[target.substr(0, 1)];
            int target_y = stoi(target.substr(1, 1)) - 1;

            coordinates.push_back(target_x);
            coordinates.push_back(target_y);
        }

        return coordinates; // coordinates = [origin_x, origin_y, target_x,
                            // target_y]
    }

    void move(string origin, string target) {
        vector<int> coordinates = map_position_to_coordinates(origin, target);
        
        for(auto i: coordinates) {
            if(i < 0 || i > 7) {
                //Testing message. Please remove later
                cout << "Out of bounds. Please enter valid coordinates" << endl;
                return;
            }
        }
       
        int origin_x = coordinates[0];
        int origin_y = coordinates[1];
        int target_x = coordinates[2];
        int target_y = coordinates[3];

        if(board[origin_x][origin_y] != nullptr) {
            bool is_valid = board[origin_x][origin_y]->is_movement_valid(origin_x, origin_y, target_x, target_y, board);

            if(is_valid) {
                board[target_x][target_y] = board[origin_x][origin_y];
                board[origin_x][origin_y] = nullptr;
            }

            //Testing message. Please remove later
            else cout << "Illegal move. Please make a valid move with the " << board[origin_x][origin_y]->getsymbol() << endl;
        }

        //Testing message. Please remove later
        else cout << "Origin is empty. There must be a piece on the origin" << endl;

    }

    void clear_board() {
        //Deletes all alocated memory space and sets null pointers
        for(int columns = 0; columns < 8; columns++) {
            for(int rows = 0; rows < 8; rows++) {
                delete board[columns][rows];
                board[columns][rows] = nullptr;
            }
        }
    }


};

// void test(Board &board) {
//     // Funcion para probar el funcionamiento del programa.
//
//     board.move("b2", "b7"); // invalido
//     board.move("b2", "b3");
//     board.move("b1", "c5"); // invalido
//     board.move("b1", "c3");
//     board.move("c3", "a5"); // invalido
//     board.move("c3", "a4");
//     board.move("c1", "a2"); // invalido
//     board.move("c1", "a3");
//     board.move("a3", "d5"); // invalido
//     board.move("a3", "d6");
//     board.move("e2", "e5"); // invalido
//     board.move("e2", "e4");
//     board.move("d1", "g5"); // invalido
//     board.move("d1", "h5");
//     board.move("h2", "h5"); // invalido
//     board.move("h2", "h4");
//     board.move("h1", "g3"); // invalido
//     board.move("h1", "h3");
//     board.move("h3", "d4"); // invalido
//     board.move("h3", "c3");
//     board.move("c3", "d7"); // invalido
//     board.move("c3", "c7");
//     board.move("e4", "e6"); // invalido
//     board.move("e4", "e5");
//     board.move("f1", "a7"); // invalido
//     board.move("f1", "a6");
//     board.display_board();
// }

#endif // BOARD_H