#pragma once
#include "figure.h"
#include <stdbool.h>

PositionedFigure random_figure();
PositionedFigure move_down(PositionedFigure figure);
PositionedFigure move_left(PositionedFigure figure);
PositionedFigure move_right(PositionedFigure figure);
PositionedFigure rotate(PositionedFigure figure);
void record_figure(PositionedFigure figure);
void unrecord_figure(PositionedFigure figure);
void run_tetris();

