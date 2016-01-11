//
// Created by Stanislav on 09/01/16.
//

#include "Window.h"

StatusWindow::StatusWindow(Display *display, WINDOW *win) : Window(display, win) {
    wbkgd(_win, COLOR_PAIR(1));
}

void StatusWindow::render(bool out) {
    werase(_win);

    waddstr(_win, "status line");

    if(out) {
        wrefresh(_win);
    } else {
        wnoutrefresh(_win);
    }
}
