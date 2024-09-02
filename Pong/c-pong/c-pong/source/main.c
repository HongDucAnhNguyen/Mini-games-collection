/**********************************************************************
 *  File:    main.c
 *  Author:  thetechnorthman
 *  Purpose: This file contains the main() function which is the driver
			 of this program.
 *  Date:    2024-08-14
 **********************************************************************/




#include "../headers/game.h"






 /**********************************************************************
  *  Driver
  **********************************************************************/




int main(void) {

	atexit(clean);
	init_game();
	run();
	return 0;
}
