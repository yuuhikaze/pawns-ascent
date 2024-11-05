#include "app-window.h"
#include "slint.h"

int main(int argc, char **argv)
{
    auto ui = AppWindow::create();
    // ui->set_maximized(true);
    // slint::Window::
    ui->window().set_maximized(true);

    ui->run();
    return 0;
}
