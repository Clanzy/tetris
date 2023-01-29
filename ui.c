#include "ui.h"
#include "constants.h"
#include "bwindow.h"

#include <ncurses.h>
#include <panel.h>
#include <stdbool.h>

void ncurses_init()
{
	initscr();
	curs_set(0);
	noecho();
	keypad(stdscr, TRUE);

	if (has_colors()) {
		start_color();
		// use_default_colors();

		init_pair(1, COLOR_BLACK, COLOR_CYAN);
		init_pair(2, COLOR_BLACK, COLOR_MAGENTA);
		init_pair(3, COLOR_BLACK, COLOR_YELLOW);
		init_pair(4, COLOR_BLACK, COLOR_YELLOW);
		init_pair(5, COLOR_BLACK, COLOR_BLUE);
		init_pair(6, COLOR_BLACK, COLOR_RED);
		init_pair(7, COLOR_BLACK, COLOR_GREEN);

		init_pair(10, COLOR_RED, COLOR_BLACK);
		init_pair(11, COLOR_YELLOW, COLOR_BLACK);
		init_pair(12, COLOR_GREEN, COLOR_BLACK);
		init_pair(13, COLOR_BLUE, COLOR_BLACK);
	}

	refresh();
}

void ncurses_del()
{
	endwin();
}

void ui_init()
{
	int starty = (LINES - HEIGHT_MAIN - BORDER) / 2;
	int startx = (COLS - WIDTH_MAIN - BORDER) / 2;
	windows[MAIN] = bwindow(HEIGHT_MAIN + BORDER, WIDTH_MAIN + BORDER,
				starty, startx);
	windows[NEXT] = bwindow(HEIGHT_NEXT + BORDER, WIDTH_NEXT + BORDER,
				starty, startx + WIDTH_MAIN + BORDER + 1);
	windows[INFO] = bwindow(HEIGHT_INFO + BORDER, WIDTH_INFO + BORDER,
				starty + HEIGHT_NEXT + BORDER + 1,
				startx + WIDTH_MAIN + BORDER + 1);
	starty = (LINES - HEIGHT_START - BORDER) / 2;
	startx = (COLS - WIDTH_START - BORDER) / 2;
	windows[START] = bwindow(HEIGHT_START + BORDER, WIDTH_START + BORDER,
				 starty, startx);
	windows[PAUSE] = bwindow(HEIGHT_PAUSE + BORDER, WIDTH_PAUSE + BORDER,
				 starty, startx);
	for (int i = 0; i < MAX_WINDOWS; i++) {
		panels[i] = dpanel(windows[i]);
	}
	hide_dpanel(panels[PAUSE]);
	wattrset(windows[NEXT]->window, COLOR_PAIR(10));
	wprintw(windows[NEXT]->window, "Next figure:");

	wattrset(windows[INFO]->window, COLOR_PAIR(11));
	mvwprintw(windows[INFO]->window, 0, 0, "Score:");
	wattrset(windows[INFO]->window, COLOR_PAIR(12));
	mvwprintw(windows[INFO]->window, 2, 0, "Level:");
	wattrset(windows[INFO]->window, COLOR_PAIR(13));
	mvwprintw(windows[INFO]->window, 4, 0, "Rows:");

	update_panels();
	doupdate();
}

void ui_del()
{
	for (int i = 0; i < MAX_WINDOWS; i++) {
		dpanel_del(panels[i]);
		bwindow_del(windows[i]);
	}
}

int ui()
{
	// TODO make START window with settings

	//int ret = getch();

	hide_dpanel(panels[START]);
	update_panels();
	doupdate();
	return /*ret*/ 0;
}
