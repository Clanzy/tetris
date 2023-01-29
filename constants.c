#include "constants.h"

BWINDOW *windows[MAX_WINDOWS];
DPANEL *panels[MAX_WINDOWS];

char game_field[HEIGHT + TOP_MARGIN][WIDTH] = { 0 };
int game_field_hash[HEIGHT + TOP_MARGIN] = { 0 };
