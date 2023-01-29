#pragma once

#include <ncurses.h>
#include <panel.h>

typedef struct bordered_window {
	WINDOW *window;
	WINDOW *border;
} bordered_window, BWINDOW;

typedef struct double_panel {
	PANEL *windowp;
	PANEL *borderp;
} double_panel, DPANEL;

BWINDOW *bwindow(int height, int width, int starty, int startx);
void bwindow_del(BWINDOW *bwin);

DPANEL *dpanel(BWINDOW *bwin);
void dpanel_del(DPANEL *dpanel);
void hide_dpanel(DPANEL *dpanel);
void show_dpanel(DPANEL *dpanel);
