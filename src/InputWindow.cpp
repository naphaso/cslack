//
// Created by Stanislav on 09/01/16.
//

#include "Window.h"

InputWindow::InputWindow(Display *display, WINDOW *win) : Window(display, win) {

}


void InputWindow::loop() {
    bool active = true;
    while(active) {
        int c = wgetch(_win);
        if(c == KEY_RESIZE) {
            _display->resize();
        } else if(c == '\f') {
            clearok(curscr, TRUE);
            _display->resize();
        } else if(c == 10) {
            //command_win_redisplay(false);
            //resize();
            active = false;
        } else {
            if(c >= 0) {
                waddch(_win, (const chtype) c);
            }
        }
    }
}

void InputWindow::render(bool out) {
    werase(_win);

    // render

    if(out) {
        wrefresh(_win);
    } else {
        wnoutrefresh(_win);
    }
}
