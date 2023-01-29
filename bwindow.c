#include "bwindow.h"
#include <stdlib.h>

WINDOW *window(int height, int width, int starty, int startx)
{
	WINDOW *win = newwin(height, width, starty, startx);

	box(win, 0, 0);
	wrefresh(win);

	return win;
}

void window_del(WINDOW *win)
{
	wborder(win, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');

	wrefresh(win);
	delwin(win);
}

BWINDOW *bwindow(int height, int width, int starty, int startx)
{
	BWINDOW *bwin = malloc(sizeof *bwin);
	bwin->border = window(height, width, starty, startx);
	bwin->window =
		newwin(height - 1 - 1, width - 1 - 1, starty + 1, startx + 1);

	// not needed because it is empty
	// wrefresh(bwin->window);

	return bwin;
}

void bwindow_del(BWINDOW *bwin)
{
	window_del(bwin->border);
	delwin(bwin->window);
	free(bwin);
}

DPANEL *dpanel(BWINDOW *bwin)
{
	DPANEL *dpanel = malloc(sizeof *dpanel);
	dpanel->borderp = new_panel(bwin->border);
	dpanel->windowp = new_panel(bwin->window);
	return dpanel;
}

void dpanel_del(DPANEL *dpanel)
{
	del_panel(dpanel->borderp);
	del_panel(dpanel->windowp);
	free(dpanel);
}
void hide_dpanel(DPANEL *dpanel)
{
	hide_panel(dpanel->windowp);
	hide_panel(dpanel->borderp);
}

void show_dpanel(DPANEL *dpanel)
{
	show_panel(dpanel->borderp);
	show_panel(dpanel->windowp);
}
