#include "board.h"
#include "app-window.h"
using namespace std;

int main(int argc, char **argv) {
    Board board;
    board.display_board();
    
    auto ui = AppWindow::create();

    ui->run();
    return 0;
}
