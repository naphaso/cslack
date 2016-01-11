//
// Created by Stanislav on 07/01/16.
//

#ifndef CSLACK_MAINLAYOUT_H
#define CSLACK_MAINLAYOUT_H

#include <ncurses.h>

class Display;

#include "Logger.h"
#include "Window.h"

class Display {
private:
    Logger _logger;

    TextWindow *_text;
    InputWindow *_input;
    StatusWindow *_status;
public:
    Display();
    ~Display();

    void loop();

    void resize();

};


#endif //CSLACK_MAINLAYOUT_H
