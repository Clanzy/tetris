#include "gameplay.h"
#include "figure.h"
#include "graphics.h"
#include "constants.h"
#include "settings.h"

#include <ncurses.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

PositionedFigure random_figure()
{
	return (PositionedFigure){ rand() % MAX_TETROMINOS,
				   0,
				   { 4, HEIGHT - 2 } };
}

static int delay_lvl[10] = { 999999, 888888, 777777, 666666, 555555,
			     444444, 333333, 222222, 111111, 100000 };
static int lvl = 0;
static int score = 0;
static int rows = 0;

void update_lvl()
{
	if (score < 1000) {
		lvl = 0;
	} else if (score >= 1000 && score < 2000) {
		lvl = 1;
	} else if (score >= 2000 && score < 3000) {
		lvl = 2;
	} else if (score >= 3000 && score < 4000) {
		lvl = 3;
	} else if (score >= 4000 && score < 5000) {
		lvl = 4;
	} else if (score >= 5000 && score < 6500) {
		lvl = 5;
	} else if (score >= 6500 && score < 9000) {
		lvl = 6;
	} else if (score >= 9000 && score < 11000) {
		lvl = 7;
	} else if (score >= 11000 && score < 13000) {
		lvl = 8;
	} else {
		lvl = 9;
	}
}

bool is_valid(PositionedFigure figure)
{
	int x = figure.position.x;
	int y = figure.position.y;
	Point *tetromino = tetrominos[figure.figure.tetromino]
				     [figure.figure.tetromino_orientation];
	for (int i = 0; i < 4; i++) {
		int currentx = x + tetromino[i].x;
		int currenty = y + tetromino[i].y;
		// checking array bounds
		if (currentx < 0 || currentx >= WIDTH) {
			return false;
		}
		if (currenty < 0 || currenty >= HEIGHT + TOP_MARGIN) {
			return false;
		}
		if (game_field[currenty][currentx] != '\0') {
			return false;
		}
	}
	return true;
}

void record_figure(PositionedFigure figure)
{
	int x = figure.position.x;
	int y = figure.position.y;
	Point *tetromino = tetrominos[figure.figure.tetromino]
				     [figure.figure.tetromino_orientation];
	for (int i = 0; i < 4; i++) {
		int currentx = x + tetromino[i].x;
		int currenty = y + tetromino[i].y;
		game_field[currenty][currentx] = '1' + figure.figure.tetromino;
		game_field_hash[currenty] += 1;
	}
}

void unrecord_figure(PositionedFigure figure)
{
	int8_t y = figure.position.y;
	int8_t x = figure.position.x;
	Point *tetromino = tetrominos[figure.figure.tetromino]
				     [figure.figure.tetromino_orientation];
	for (int i = 0; i < 4; i++) {
		int currentx = x + tetromino[i].x;
		int currenty = y + tetromino[i].y;
		game_field[currenty][currentx] = '\0';
		game_field_hash[currenty] -= 1;
	}
}

void remove_row_from_game_field(int row)
{
	for (int i = row; i < HEIGHT; i++) {
		for (int j = 0; j < WIDTH; j++) {
			game_field[i][j] = game_field[i + 1][j];
		}
		game_field_hash[i] = game_field_hash[i + 1];
	}
}

int check_if_row_full()
{
	int count = 0;
	for (int i = 0; i < HEIGHT; i++) {
		if (game_field_hash[i] == WIDTH) {
			remove_row_from_game_field(i);
			count++;
			i--;
		}
	}
	for (int i = HEIGHT; i < HEIGHT + TOP_MARGIN; i++) {
		if (game_field_hash[i] != 0) {
			return 1;
		}
	}
	switch (count) {
	case 1:
		score += 100;
		rows += 1;
		break;
	case 2:
		score += 300;
		rows += 2;
		break;
	case 3:
		score += 500;
		rows += 3;
		break;
	case 4:
		score += 800;
		rows += 4;
		break;
	default:
		return 0;
		break;
	}

	update_lvl();
	display_score(score);
	display_lvl(lvl);
	display_rows(rows);
	redraw_game_field();
	return 0;
}

PositionedFigure move_down(PositionedFigure figure)
{
	PositionedFigure figure_copy = figure;
	figure_copy.position.y -= 1;
	if (is_valid(figure_copy)) {
		clear_figure(figure);
		display_figure(figure_copy);
		return figure_copy;
	}
	return figure;
}

PositionedFigure move_left(PositionedFigure figure)
{
	PositionedFigure figure_copy = figure;
	figure_copy.position.x -= 1;
	if (is_valid(figure_copy)) {
		clear_figure(figure);
		display_figure(figure_copy);
		return figure_copy;
	}
	return figure;
}

PositionedFigure move_right(PositionedFigure figure)
{
	PositionedFigure figure_copy = figure;
	figure_copy.position.x += 1;
	if (is_valid(figure_copy)) {
		clear_figure(figure);
		display_figure(figure_copy);
		return figure_copy;
	}
	return figure;
}

PositionedFigure rotate(PositionedFigure figure)
{
	PositionedFigure figure_copy = figure;
	figure_copy.figure.tetromino_orientation =
		(figure_copy.figure.tetromino_orientation + 1) % 4;
	if (is_valid(figure_copy)) {
		clear_figure(figure);
		display_figure(figure_copy);
		return figure_copy;
	}
	return figure;
}

void run_tetris()
{

	display_score(score);
	display_lvl(lvl);
	display_rows(rows);
	
	PositionedFigure next_f = random_figure();

	for (;;) {
		struct timeval start, delay;
		gettimeofday(&start, NULL);
		fd_set readfds, temp_readfds;

		delay.tv_sec = 0;
		delay.tv_usec = delay_lvl[lvl];

		FD_ZERO(&readfds);
		FD_SET(0, &readfds);

		PositionedFigure f = next_f;
		PositionedFigure temp_f;
		next_f = random_figure();
		display_figure(f);
		display_next(next_f);
		for (;;) {
			temp_readfds = readfds;

			int sel_ret = select(0 + 1, &temp_readfds, NULL, NULL,
					     &delay);
			if (sel_ret == 0) {
				temp_f = move_down(f);
				if (temp_f.position.y == f.position.y) {
					record_figure(temp_f);
					if (check_if_row_full() == 1) {
						return;
					};
					break;
				}
				delay.tv_sec = 0;
				delay.tv_usec = delay_lvl[lvl];
			} else {
				int i = getch();
				if (i == move_down_key_1 ||
				    i == move_down_key_2) {
					temp_f = move_down(f);
					if (temp_f.position.y == f.position.y) {
						record_figure(temp_f);
						if (check_if_row_full() == 1) {
							return;
						};
						break;
					}

				} else if (i == move_left_key_1 ||
					   i == move_left_key_2) {
					temp_f = move_left(f);

				} else if (i == move_right_key_1 ||
					   i == move_right_key_2) {
					temp_f = move_right(f);

				} else if (i == rotate_key_1 ||
					   i == rotate_key_2) {
					temp_f = rotate(f);
				} else if (i == drop_piece_key_1 ||
					   i == drop_piece_key_2) {
					while ((temp_f = move_down(f))
						       .position.y !=
					       f.position.y) {
						f = temp_f;
					}
					record_figure(temp_f);
					if (check_if_row_full() == 1) {
						return;
					};
					break;

				} else {
					continue;
				}
			}
			f = temp_f;
		}
		clear_next(next_f);
	}
}
