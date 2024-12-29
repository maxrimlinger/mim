/**
 * @file display.c
 * @author Max Rimlinger
 *
 * Functions to display the program onto the ncurses window
 */

#include <string.h>
#include <ncurses.h>

#include "types.h"

size_t min(size_t a, size_t b) {
    return a < b ? a : b;
}

void move_cur(View view) {
    move(view.cur.line - view.top_line, view.cur.ch - view.left_ch);
}

/** 
 * Prints the contents of a FileProxy to the ncurses stdscr
 *
 * @param fp the FileProxy to print
 * @param view meta information about where the cursor is and where we are panned
 *      in the file
 */
void display_fp(FileProxy fp, View view) {
    size_t line_limit = min(view.top_line + view.vlimit, fp.len);
    for (size_t i = view.top_line; i < line_limit; i++) {
        Line line = *fp.lines[i];
        size_t char_limit = min(view.left_ch + view.hlimit, line.len);
        for (size_t j = view.left_ch; j < char_limit; j++) {
            mvaddch(i - view.top_line, j - view.left_ch, line.text[j]);
        }
    }
}

void display_status_bar(MimState ms) {
    // mode
    char *mode_str = "";
    if (ms.mode == INSERT) {
        mode_str = "-- INSERT --";
    }
    move(LINES - 1, 0);
    printw("%s", mode_str);
    
    // message
    // FIXME buncha weird stuff appears if you move around after a msg is displayed
    if (ms.status_msg != NULL) {
        move(LINES - 1, COLS - 1 - strlen(ms.status_msg));
        printw("%s", ms.status_msg);
    }
}

void display(MimState ms, FileProxy fp, View view) {
    erase();

    display_fp(fp, view);
    display_status_bar(ms);
    move_cur(view);

    refresh();
}

