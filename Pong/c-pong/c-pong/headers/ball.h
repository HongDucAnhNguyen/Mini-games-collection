#include <stdlib.h>
#include <time.h>
#pragma once
typedef struct Ball {
	float x; // the ball's x position in sdl window
	float y; // the ball's y position in sdl window
	float width; // the ball's width
	float height; // the ball's height
	float speedX; // the ball's speed on x-axis
	float speedY; // the ball's speed on y-axis
} Ball;


Ball create_ball();
SDL_Rect create_ball_rect(const Ball* ball);


void update_ball(float delta_time, Ball* ball);

void render_ball(const Ball* ball);




/**
 * Function: random_ball_direction
 * --------------------
 * acts like a coin flip
 * if false ball's direction is inversed upon game start, otherwise it stays the same
 *  returns: integer value of either 1 (true) or 0 (false)
 */

int random_ball_direction();