#include "board.h"
#include "app-window.h"
using namespace std;


 void test_moves(int n, Board &board) {

    string origin;
    string target;
        
    for(int i = 0; i < n; i++) {  
    cout << "origin: ";
    cin >> origin;
    cout << endl;

    cout << "target: ";
    cin >> target;
    cout << endl;

    board.move(origin, target);

    board.display_board();
    }
    
 }

int main(int argc, char **argv) {
    Board board;

    board.display_board();

    test_moves(10, board);

    board.clear_board();

    auto ui = AppWindow::create();
    ui->run();

    return 0;
}
