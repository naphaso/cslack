//
// Created by Stanislav on 09/01/16.
//

#include "Window.h"

TextWindow::TextWindow(Display *display, WINDOW *win) : Window(display, win) {
    scrollok(_win, TRUE);
}

void TextWindow::render(bool out) {
    werase(_win);

    // render

    if(out) {
        wrefresh(_win);
    } else {
        wnoutrefresh(_win);
    }
}
