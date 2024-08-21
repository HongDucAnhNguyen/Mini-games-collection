#pragma once
typedef struct Player {

	int score;
	float width;
	float height;
	float y;
	int x;
	float speed;

} Player;


Player create_first_player();
Player create_second_player();
SDL_Rect create_player_rect(const Player* player);
float clamp_movement_boundary(float value, float min, float max);

void update_players(float delta_time, Player* player1, Player* player2);

void render_player(const Player* player);