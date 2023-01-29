#pragma once

#include "bwindow.h"
#include <stdbool.h>

// UI constants

typedef enum Windows {
	MAIN = 0,
	NEXT = 1,
	INFO = 2,
	START = 3,
	PAUSE = 4,
	MAX_WINDOWS
} Windows;

#define HEIGHT_MAIN 20
#define WIDTH_MAIN 20
#define HEIGHT_NEXT 6
#define WIDTH_NEXT 16
#define HEIGHT_INFO 6
#define WIDTH_INFO WIDTH_NEXT
#define HEIGHT_START 4
#define WIDTH_START 28
#define HEIGHT_PAUSE HEIGHT_START
#define WIDTH_PAUSE WIDTH_START

#define BORDER 2

extern BWINDOW *windows[];
extern DPANEL *panels[];

// gameplay constants

#define WIDTH 10
#define HEIGHT 20
#define TOP_MARGIN 2

extern char game_field[][WIDTH];
extern int game_field_hash[];
