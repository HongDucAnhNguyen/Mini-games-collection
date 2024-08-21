#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include <SDL_ttf.h>
#include "../headers/ball.h"
#include "../headers/player.h"
#include "../headers/constants.h"







// Global variables
extern SDL_Window* window;
extern SDL_Renderer* renderer;
extern SDL_Event event;
extern int game_is_running;
extern int start_match;
extern float delta_time;
extern TTF_Font* font; // 24 is the font size




// Function prototypes
void init_game(void);
void process_inputs(void);
void update(float delta_time);
void reset_match(Ball* ball);
void update_score(int* player_score);
void render(void);
void clean(void);
void run(void);

void render_score(SDL_Renderer* renderer, TTF_Font* font, int score1, int score2);







#endif // GAME_H
