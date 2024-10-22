#include "app-window.h"

int main(int argc, char **argv)
{
    auto ui = AppWindow::create();

    ui->run();
    return 0;
}
