//
// Created by Stanislav on 07/01/16.
//

#include <stdlib.h>
#include <stdio.h>
#include <ncurses.h>
#include <locale.h>
#include "Display.h"
#include "Exception.h"

Display::Display() : _logger("/tmp/cslack.log") {
    setlocale(LC_ALL, "");
    if(initscr() == NULL) {
        throw Exception("failed to initialize terminal");
    }

    start_color();
    use_default_colors();

    cbreak();
    noecho();
    nonl();
    //intrflush(NULL, FALSE);
    init_pair(1, COLOR_WHITE, COLOR_BLUE);

    if (LINES >= 3) {
        _text = new TextWindow(this, newwin(LINES - 2, COLS, 0, 0));
        _status = new StatusWindow(this, newwin(1, COLS, LINES - 2, 0));
        _input = new InputWindow(this, newwin(1, COLS, LINES - 1, 0));
    } else {
        _text = new TextWindow(this, newwin(1, COLS, 0, 0));
        _status = new StatusWindow(this, newwin(1, COLS, 0, 0));
        _input = new InputWindow(this, newwin(1, COLS, 0, 0));
    }
}

Display::~Display() {
    delete _status;
    delete _text;
    delete _input;
    endwin();
}

void Display::loop() {
    _input->loop();
}

void Display::resize() {
    if(LINES > 3) {
        wresize(_text->win(), LINES - 2, COLS);
        wresize(_status->win(), 1, COLS);
        wresize(_input->win(), 1, COLS);

        mvwin(_status->win(), LINES - 2, 0);
        mvwin(_input->win(), LINES - 1, 0);
    }

    _text->render(false);
    _status->render(false);
    _input->render(false);

    doupdate();
}
