#include "board.h"
// #include "app-window.h"
using namespace std;

void test_moves(int n, Board &board) {

    string origin;
    string target;
    bool turn = true;

    cout << "\033[2J\033[1;1H";
    cout << "Current turn: ";
    if (turn)
        cout << "White " << endl;
    else
        cout << "Black " << endl;
    board.display_board();

    int i = 0;
    while (i < n) {
        cout << "origin: ";
        cin >> origin;
        cout << endl;

        cout << "target: ";
        cin >> target;
        cout << endl;

        cout << "\033[2J\033[1;1H";
        
        if (board.move(origin, target, turn)) {
            turn = !turn;
            i++;
        }

        if(GameState::is_checkmated_black || GameState::is_checkmated_black || GameState::is_stalemate || GameState::is_insufficient_material)
            break;

        cout << "Current turn: ";
        if (turn)
            cout << "White " << endl;
        else
            cout << "Black " << endl;
        
        board.display_board();
    }

    if(GameState::is_checkmated_black) {
        cout << "White wins! (I hate my life)" << endl;
    }

    if(GameState::is_checkmated_white) {
        cout << "Black wins! (I hate my life)" << endl;
    }

    if(GameState::is_stalemate) {
        cout << "Stalemate... It's a tie" << endl;
    }

    if(GameState::is_insufficient_material) {
        cout << "Insufficient material... It's a tie";
    }
}

int main(int argc, char **argv) {
    Board board;

    test_moves(30, board);

    board.clear_board();

    // auto ui = AppWindow::create();
    // ui->window().set_maximized(true)
    // ui->run();

    return 0;
}
