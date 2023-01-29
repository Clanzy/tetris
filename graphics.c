#include "graphics.h"

#include "constants.h"
#include "figure.h"
#include <stdbool.h>
#include <ncurses.h>
#include "bwindow.h"

void toggle_pause()
{
	static bool displayed = false;
	if (displayed) {
		hide_dpanel(panels[PAUSE]);
	} else {
		show_dpanel(panels[PAUSE]);
	}
	displayed = !displayed;
	update_panels();
	doupdate();
}

void display_figure(PositionedFigure pfigure)
{
	WINDOW *this = windows[MAIN]->window;
	int8_t y = HEIGHT_MAIN - 1 - pfigure.position.y;
	int8_t x = pfigure.position.x;
	Point *tetromino = tetrominos[pfigure.figure.tetromino]
				     [pfigure.figure.tetromino_orientation];
	for (int i = 0; i < 4; i++) {
		wattrset(this, COLOR_PAIR(pfigure.figure.tetromino + 1));

		mvwaddstr(this, y - tetromino[i].y, (x + tetromino[i].x) * 2,
			  "  ");
	}
	wrefresh(this);
}

void clear_figure(PositionedFigure pfigure)
{
	WINDOW *this = windows[MAIN]->window;
	int8_t y = HEIGHT_MAIN - 1 - pfigure.position.y;
	int8_t x = pfigure.position.x;
	Point *tetromino = tetrominos[pfigure.figure.tetromino]
				     [pfigure.figure.tetromino_orientation];
	for (int i = 0; i < 4; i++) {
		wattrset(this, COLOR_PAIR(0));

		mvwaddstr(this, y - tetromino[i].y, (x + tetromino[i].x) * 2,
			  "  ");
	}
	wrefresh(this);
}

void redraw_game_field()
{
	WINDOW *this = windows[MAIN]->window;
	wclear(this);
	for (int i = 0; i < HEIGHT; i++) {
		for (int j = 0; j < WIDTH; j++) {
			wattrset(this, COLOR_PAIR(game_field[i][j] - '0'));
			mvwaddstr(this, HEIGHT_MAIN - 1 - i, j * 2, "  ");
		}
	}
	wrefresh(this);
}

void display_next(PositionedFigure pfigure)
{
	WINDOW *this = windows[NEXT]->window;
	int8_t y = HEIGHT_NEXT - 1;
	int8_t x = 2;
	Point *tetromino = tetrominos[pfigure.figure.tetromino]
				     [pfigure.figure.tetromino_orientation];
	for (int i = 0; i < 4; i++) {
		wattrset(this, COLOR_PAIR(pfigure.figure.tetromino + 1));

		mvwaddstr(this, y - tetromino[i].y, (x + tetromino[i].x) * 2,
			  "  ");
	}
	wrefresh(this);
}

void clear_next(PositionedFigure pfigure)
{
	WINDOW *this = windows[NEXT]->window;
	int8_t y = HEIGHT_NEXT - 1;
	int8_t x = 2;
	Point *tetromino = tetrominos[pfigure.figure.tetromino]
				     [pfigure.figure.tetromino_orientation];
	for (int i = 0; i < 4; i++) {
		wattrset(this, COLOR_PAIR(0));

		mvwaddstr(this, y - tetromino[i].y, (x + tetromino[i].x) * 2,
			  "  ");
	}
	wrefresh(this);
}

void display_score(int score)
{
	wattrset(windows[INFO]->window, COLOR_PAIR(11));
	WINDOW *this = windows[INFO]->window;
	mvwprintw(this, 1, 0, "%d", score);
	wrefresh(this);
}

void display_lvl(int lvl)
{
	wattrset(windows[INFO]->window, COLOR_PAIR(12));
	WINDOW *this = windows[INFO]->window;
	mvwprintw(this, 3, 0, "%d", lvl);
	wrefresh(this);
}

void display_rows(int rows)
{
	wattrset(windows[INFO]->window, COLOR_PAIR(13));
	WINDOW *this = windows[INFO]->window;
	mvwprintw(this, 5, 0, "%d", rows);
	wrefresh(this);
}
