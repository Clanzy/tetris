#pragma once

#include <stdint.h>

typedef struct Point {
	int8_t x;
	int8_t y;
} Point;

typedef Point tetromino[4][4];

typedef enum Tetromino {
	I = 0,
	T = 1,
	O = 2,
	L = 3,
	J = 4,
	Z = 5,
	S = 6,
	MAX_TETROMINOS
} Tetromino;

extern tetromino tetrominos[MAX_TETROMINOS];

typedef struct Figure {
	Tetromino tetromino;
	int8_t tetromino_orientation;
} Figure;

typedef struct PositionedFigure {
	Figure figure;
	Point position;
} PositionedFigure;
