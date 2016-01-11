#include <ncurses.h>
#include <termios.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <wchar.h>
#include <typeinfo>
#include <string>
#include <locale.h>


#include "Logger.h"
#include "Display.h"

WINDOW *main_win;
WINDOW *status_win;
WINDOW *command_win;

std::wstring main_text(L"hello world");
std::wstring command_line;
std::wstring command_prompt(L"cmd> ");



void main_win_redisplay(bool for_resize) {
    werase(main_win);

    mvwaddstr(main_win, 0, 0, (const char *) main_text.c_str());

    // We batch window updates when resizing.
    if (for_resize)
        wnoutrefresh(main_win);
    else
        wrefresh(main_win);
}

void command_win_redisplay(bool for_resize) {
    size_t prompt_width = command_prompt.size();
    size_t cursor_col = prompt_width;

    werase(command_win);
    // This might write a string wider than the terminal currently, so don't
    // check for errors.
    mvwprintw(command_win, 0, 0, "%s%s", command_prompt.c_str(), command_line.c_str());
    if (cursor_col >= COLS)
        // Hide the cursor if it lies outside the window. Otherwise it'll
        // appear on the very right.
        curs_set(0);
    else {
        wmove(command_win, 0, (int) cursor_col);
        curs_set(2);
    }

    // We batch window updates when resizing.
    if (for_resize)
        wnoutrefresh(command_win);
    else
        wrefresh(command_win);
}

void resize() {
    if(LINES > 3) {
        wresize(main_win, LINES - 2, COLS);
        wresize(status_win, 1, COLS);
        wresize(command_win, 1, COLS);

        mvwin(status_win, LINES - 2, 0);
        mvwin(command_win, LINES - 1, 0);
    }

    main_win_redisplay(true);
    wnoutrefresh(status_win);
    command_win_redisplay(true);
    doupdate();
}

void init_ncurses() {
    setlocale(LC_ALL, "");
    if(initscr() == NULL) {
        printf("failed to initialize\n");
        exit(0);
    }

    if(can_change_color()) {
        start_color();
        use_default_colors();
    }

    cbreak();
    noecho();
    nonl();
    intrflush(NULL, FALSE);

    curs_set(2);

    if (LINES >= 3) {
        main_win = newwin(LINES - 2, COLS, 0, 0);
        status_win = newwin(1, COLS, LINES - 2, 0);
        command_win = newwin(1, COLS, LINES - 1, 0);
    } else {
        // Degenerate case. Give the windows the minimum workable size to
        // prevent errors from e.g. wmove().
        main_win = newwin(1, COLS, 0, 0);
        status_win = newwin(1, COLS, 0, 0);
        command_win = newwin(1, COLS, 0, 0);
    }

    if (main_win == NULL || status_win == NULL || command_win == NULL) {
        printf("Failed to allocate windows\n");
        exit(0);
    }

    scrollok(main_win, TRUE);
    if(can_change_color()) {
        init_pair(1, COLOR_WHITE, COLOR_BLUE);
        wbkgd(status_win, COLOR_PAIR(1));
    } else {
        wbkgd(status_win, A_STANDOUT);
    }

    wrefresh(status_win);
}

void deinit_ncurses(void) {
    delwin(main_win);
    delwin(status_win);
    delwin(command_win);
    endwin();
}


int main() {
    /*
    //struct termios tio;
    Logger _logger("/tmp/cslack.log");
    init_ncurses();

    bool should_exit = false;
    while(!should_exit) {
        int c = wgetch(command_win);

        if(c == KEY_RESIZE) {
            resize();
        } else if(c == '\f') {
            clearok(curscr, TRUE);
            resize();
        } else if(c == 10) {
            command_win_redisplay(false);
            resize();
        } else {
            // just symbol
            if(c >= 0) {
                waddch(command_win, (const chtype) c);
            }
        }
    }
     */

    Display display;
    display.loop();

    //deinit_ncurses();

    //idlok(stdscr, true);

    //intrflush(stdscr, false);
    //nodelay(stdscr, true);
    //keypad(stdscr, TRUE);


    /*
    if (tcgetattr(0, &old_tio) == 0) {
        memcpy(&tio, &old_tio, sizeof(tio));
        tio.c_cc[VINTR] = _POSIX_VDISABLE;
        tio.c_cc[VQUIT] = _POSIX_VDISABLE;
        //#ifdef VDSUSP
        tio.c_cc[VDSUSP] = _POSIX_VDISABLE;
        //#endif
        //#ifdef VSUSP
        tio.c_cc[VSUSP] = _POSIX_VDISABLE;
        //#endif
        tcsetattr(0, TCSADRAIN, &tio);
    }

    if(has_colors()) {
        start_color();
    } else {
        // colors not found
    }

     */


    /*

    WINDOW * win = newwin(10, 10, 10, 10);

    for(int i = 0; i < 1000; i ++) {
        waddch(win, 'X' | COLOR_PAIR(4));
    }

    wrefresh(win);
     */



    return 0;
}