//
// Created by Stanislav on 07/01/16.
//

#ifndef CSLACK_WINDOW_H
#define CSLACK_WINDOW_H


#include <ncurses.h>

class Window;
class InputWindow;
class StatusWindow;
class TextWindow;

#include "Display.h"

class Window {
protected:
    Display *_display;
    WINDOW *_win;
public:
    Window(Display *display, WINDOW *win) : _display(display), _win(win) {}
    virtual ~Window() { delwin(_win); }
    virtual void render(bool out) = 0;
    WINDOW *win() { return _win; };
};


class StatusWindow : public Window {
public:
    StatusWindow(Display *display, WINDOW *win);


    virtual void render(bool out) override;
};

class TextWindow : public Window {
public:
    TextWindow(Display *display, WINDOW *win);

    virtual void render(bool out) override;
};

class InputWindow : public Window {
public:
    InputWindow(Display *display, WINDOW *win);

    virtual void render(bool out) override;

    void loop();
};

#endif //CSLACK_WINDOW_H
