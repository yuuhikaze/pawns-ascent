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

        cout << "Current turn: ";
        if (turn)
            cout << "White " << endl;
        else
            cout << "Black " << endl;
        
        board.display_board();
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
