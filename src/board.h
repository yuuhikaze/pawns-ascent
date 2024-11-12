#ifndef BOARD_H
#define BOARD_H

#include "pieces/bishop.h"
#include "pieces/king.h"
#include "pieces/knight.h"
#include "pieces/pawn.h"
#include "pieces/queen.h"
#include "pieces/rook.h"

using namespace std;

class Board {
  private:
    vector<vector<Piece *>> board;

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
    }


  public:
    Board() { initialize_board(); }

    void initialize_board() {

        board.resize(8, vector<Piece *>(8, nullptr));

        // board[0][7] = new Rook(false);
        board[7][7] = new Rook(false);

        board[1][7] = new Knight(false);
        // board[6][7] = new Knight(false);

        // board[2][7] = new Bishop(false);
        board[5][7] = new Bishop(false);

        board[3][7] = new Queen(false);
        board[4][7] = new King (false);

        // for(int column = 0; column < 8; column+=3) {
        //     board[column][3] =  new Pawn(false);
        // }

        board[0][0] = new Rook(true);
        // board[7][0] = new Rook(true);

        // board[1][0] = new Knight(true);
        // board[6][0] = new Knight(true);

        // board[2][0] = new Bishop(true);
        // board[5][0] = new Bishop(true);

        // board[3][0] = new Queen(true);
        board[4][0] = new King(true);

        // for (int column = 0; column < 8; column++) {
        //     board[column][1] = new Pawn(true);
        // }
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

    void move(const string &origin_string, const string &target_string) {
        if(origin_string == target_string) {
            cout << "Same origin and target" << endl;
            return;
        }
        
        vector<int> move = map_position_to_coordinates(origin_string, target_string);

        for (auto i : move) {
            if (i < 0 || i > 7) {
                // Testing message. Please remove later
                cout << "Out of bounds. Please enter valid coordinates" << endl;
                return;
            }
        }

        coordinates origin(move[0], move[1]);
        coordinates target(move[2], move[3]);

        if (board[origin.x][origin.y] != nullptr) {
            bool is_valid = board[origin.x][origin.y]->is_movement_valid(origin, target, board);

            if (is_valid) {
                board[target.x][target.y] = board[origin.x][origin.y];
                board[origin.x][origin.y] = nullptr;

                cout << "Possible moves: " << endl;

                vector<coordinates> moves = board[target.x][target.y]->getmoves(target, board);

                for(auto i: moves) {
                    cout << "x: " << i.x << "  y: " << i.y << endl;
                }

                if (target.y == 7 && dynamic_cast<Pawn *>(board[target.x][target.y]))
                    promote(target);
            }

            // Testing message. Please remove later
            else
                cout << "Illegal move. Please make a valid move with the "
                     << board[origin.x][origin.y]->getsymbol() << endl;
        }

        // Testing message. Please remove later
        else
            cout << "Origin is empty. There must be a piece on the origin" << endl;
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

};

//     void test(Board &board) {
//     // Funcion para probar el funcionamiento del programa.

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
