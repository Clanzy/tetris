#include "ui.h"
#include "gameplay.h"

#include <stdlib.h>
#include <time.h>



int main()
{
	srand(time(NULL));
	ncurses_init();
	ui_init();
	ui();

	// gameplay here
	run_tetris();

	ui_del();
	ncurses_del();

	return 0;
}
