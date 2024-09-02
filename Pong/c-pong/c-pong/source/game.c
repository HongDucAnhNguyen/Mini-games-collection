#include <stdio.h>
#include <stdlib.h>
#include "../headers/game.h"



/**********************************************************************
  *  Global variables
  **********************************************************************/

int last_frame_time = 0; //how much time elapsed since the last frame was called

Ball g_ball = { 0 };

Player g_player1 = { 0 };
Player g_player2 = { 0 };
//Player ai_player = { 0 };

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
SDL_Event event = { 0 };
int game_is_running = FALSE;
int start_match = FALSE;
float delta_time = 0.0f;
TTF_Font* font = NULL;






/**********************************************************************
 *  Ball related
 **********************************************************************/

Ball create_ball() {

	//centering the ball on the window
	g_ball.x = BALL_X_POS;
	g_ball.y = BALL_Y_POS;
	g_ball.width = BALL_WIDTH;
	g_ball.height = BALL_HEIGHT;
	g_ball.speedX = BALL_SPEED_X * (random_ball_direction() ? 1 : -1);
	g_ball.speedY = BALL_SPEED_Y * (random_ball_direction() ? 1 : -1);
	return g_ball;
}


void render_ball(const Ball* ball) {

	SDL_Rect ball_rect = CREATE_RECT(ball);
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderFillRect(renderer, &ball_rect);
}


void update_ball(float delta_time, Ball* ball) {
	ball->x += delta_time * ball->speedX;
	ball->y += delta_time * ball->speedY;

	if (ball->x <= 0 - ball->width / 2) {
		reset_match(ball);
		update_score(&(g_player2.score));
		printf("player1 score: %d\n", g_player1.score);
		printf("player2 score: %d\n", g_player2.score);
	}
	if (ball->x + ball->width / 2 >= WINDOW_WIDTH) {
		reset_match(ball);
		update_score(&(g_player1.score));
		printf("player1 score: %d\n", g_player1.score);
		printf("player2 score: %d\n", g_player2.score);

	}
	if (ball->y <= 0 - ball->height / 2 || ball->y + ball->height / 2 >= WINDOW_HEIGHT) {
		ball->speedY *= -1;


	}



}


int random_ball_direction() {
	// Seed the random number generator with the current time
	srand(time(NULL));

	// Generate a random number, then modulate by 2 to get a value of 0 or 1
	return rand() % 2;
}


/**********************************************************************
 *  Player related
 **********************************************************************/
Player create_first_player() {
	g_player1.score = 0;
	g_player1.x = PLAYER_MARGIN;
	g_player1.y = PLAYER_Y_POS;
	g_player1.width = PLAYER_WIDTH;
	g_player1.height = PLAYER_HEIGHT;
	g_player1.speed = PLAYER_SPEED;
	return g_player1;
}
Player create_second_player() {
	g_player2.score = 0;
	g_player2.x = WINDOW_WIDTH - PLAYER_WIDTH - PLAYER_MARGIN;
	g_player2.y = PLAYER_Y_POS;
	g_player2.width = PLAYER_WIDTH;
	g_player2.height = PLAYER_HEIGHT;
	g_player2.speed = PLAYER_SPEED;
	return g_player2;
}


float clamp_movement_boundary(float value, float min, float max)
{

	if (value < min) return min;
	if (value > max) return max;
	return value;

}



void update_players(float delta_time, Player* player1, Player* player2)
{
	const Uint8* keyboard_state = SDL_GetKeyboardState(NULL);




	if (keyboard_state[SDL_SCANCODE_W]) {
		player1->y -= player1->speed * delta_time;
	}

	if (keyboard_state[SDL_SCANCODE_S]) {
		player1->y += player1->speed * delta_time;
	}

	if (keyboard_state[SDL_SCANCODE_UP]) {
		player2->y -= player2->speed * delta_time;
	}

	if (keyboard_state[SDL_SCANCODE_DOWN]) {
		player2->y += player2->speed * delta_time;
	}

	player1->y = clamp_movement_boundary(player1->y, 0, WINDOW_HEIGHT - player1->height);
	player2->y = clamp_movement_boundary(player2->y, 0, WINDOW_HEIGHT - player2->height);


	SDL_Rect ball_rect = CREATE_RECT(&g_ball);
	SDL_Rect player1_rect = CREATE_RECT(player1);

	SDL_Rect player2_rect = CREATE_RECT(player2);




	if (SDL_HasIntersection(&ball_rect, &player1_rect)) {
		g_ball.speedX *= -1;

	}
	if (SDL_HasIntersection(&ball_rect, &player2_rect)) {
		g_ball.speedX *= -1;

	}

}

void render_player(const Player* player)
{


	SDL_Rect player_rect = CREATE_RECT(player);


	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderFillRect(renderer, &player_rect);
}




/**********************************************************************
 *  Game related
 **********************************************************************/

void init_game(void) {





	//at this point, sdl keeps track of ticks
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		fprintf(stderr, "Error initializing SDL: %s\n", SDL_GetError());
		exit(1);
	}
	if (TTF_Init() == -1) {
		fprintf(stderr, "Failed to initialize SDL_ttf: %s\n", TTF_GetError());
		exit(1);
	}


	font = TTF_OpenFont("./assets/fonts/main-font.ttf", 24);
	if (!font) {
		fprintf(stderr, "Failed to load font: %s\n", TTF_GetError());
		exit(1);
	}
	printf("font loaded\n");


	window = SDL_CreateWindow("Pong with C",
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);

	if (!window) {
		fprintf(stderr, "Error creating SDL Window: %s\n", SDL_GetError());
		SDL_Quit();
		exit(1);
	}

	renderer = SDL_CreateRenderer(window, -1, 0, SDL_RENDERER_PRESENTVSYNC);
	if (!renderer) {
		fprintf(stderr, "Error creating SDL Renderer: %s\n", SDL_GetError());
		SDL_DestroyWindow(window);
		SDL_Quit();
		exit(1);
	}

	game_is_running = TRUE;

	g_ball = create_ball();
	g_player1 = create_first_player();
	g_player2 = create_second_player();



}

void process_inputs(void) {
	SDL_PollEvent(&event);
	switch (event.type) {
	case SDL_QUIT:
		game_is_running = FALSE;
		break;
	case SDL_KEYDOWN:
		if (event.key.keysym.sym == SDLK_ESCAPE) {
			game_is_running = FALSE;
		}

		break;
	}

}


void update(float delta_time) {




	update_ball(delta_time, &g_ball);
	update_players(delta_time, &g_player1, &g_player2);






}

void reset_match(Ball* ball)
{
	ball->x = WINDOW_WIDTH / 2 - (ball->width / 2);
	ball->y = WINDOW_HEIGHT / 2 - (ball->height / 2);
}

void update_score(int* player_score)
{
	*player_score += POINTS_GAINED;
}

void render_score(SDL_Renderer* renderer, TTF_Font* font, int score1, int score2) {
	SDL_Color white = { 255, 255, 255 }; // Text color

	char score_text[10];
	SDL_Surface* surface;
	SDL_Texture* texture;
	SDL_Rect dest_rect;

	// fill score_text buffer player by player
	sprintf_s(score_text, sizeof(score_text), "%d", score1);

	// render player1 text
	surface = TTF_RenderText_Solid(font, score_text, white);
	texture = SDL_CreateTextureFromSurface(renderer, surface);
	dest_rect.x = WINDOW_WIDTH / 2 - 50; // Position on the X-axis
	dest_rect.y = 20; // Position on the Y-axis
	dest_rect.w = surface->w;
	dest_rect.h = surface->h;

	//free resources, move on to player2 text
	SDL_FreeSurface(surface);
	SDL_RenderCopy(renderer, texture, NULL, &dest_rect);
	SDL_DestroyTexture(texture);


	sprintf_s(score_text, sizeof(score_text), "%d", score2);
	surface = TTF_RenderText_Solid(font, score_text, white);
	texture = SDL_CreateTextureFromSurface(renderer, surface);
	dest_rect.x = WINDOW_WIDTH / 2 + 50; // Position on the X-axis
	dest_rect.y = 20; // Position on the Y-axis
	dest_rect.w = surface->w;
	dest_rect.h = surface->h;

	//free resources, loop over
	SDL_FreeSurface(surface);
	SDL_RenderCopy(renderer, texture, NULL, &dest_rect);
	SDL_DestroyTexture(texture);
}


void render(void) {
	// Rendering logic here
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

	SDL_RenderClear(renderer);


	render_player(&g_player1);
	render_player(&g_player2);
	render_ball(&g_ball);

	// Render the scores
	render_score(renderer, font, g_player1.score, g_player2.score);

	//swap buffers
	SDL_RenderPresent(renderer);

}

void clean(void) {
	// Clean up
	if (font) {
		TTF_CloseFont(font);
		TTF_Quit();
	}

	if (renderer) {

		SDL_DestroyRenderer(renderer);
	}
	if (window) {

		SDL_DestroyWindow(window);
	}


	printf("Cleaned resources, exiting game...Goodbye!\n");
	SDL_Quit();
}

void run(void) {
	while (game_is_running) {
		process_inputs();


		/*while current time not passed estimated time for a frame to be processed,
	halt execution

	SDL_TICKS_PASSED compares 32-bit SDL tick values, return true if A passed B
	 SDL_TICKS_PASSED (A, B)

	 while (

		!SDL_TICKS_PASSED(
			SDL_GetTicks(),//GetTicks() return how many ticks (how much ms) have elapsed since Init() call

			last_frame_time + TIME_PER_FRAME_TARGET_MS
		));

	 */


		int delay_time = TIME_PER_FRAME_TARGET_MS - (SDL_GetTicks() - last_frame_time);


		//second condition handles possible value wrapping
		if (delay_time > 0 && delay_time <= TIME_PER_FRAME_TARGET_MS) {

			SDL_Delay(delay_time);
		}



		//difference in ticks from last frame (converted to seconds)
		float delta_time = (SDL_GetTicks() - last_frame_time) / 1000.0f;

		//last frame time = current time
		last_frame_time = SDL_GetTicks();


		update(delta_time);

		render();
	}
}

