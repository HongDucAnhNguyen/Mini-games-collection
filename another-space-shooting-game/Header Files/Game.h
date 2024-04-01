#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Network.hpp>

#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"
#include "Framerate.h"
#include "Math.h"
#include "SpaceRock.h"


/*Game engine wrapper class*/

class Game
{

private:

	/*state variables*/

	sf::Uint32 currentState;



	//game states
	enum game_state
	{
		s_running,
		s_intro,
		s_menu,
		s_info,
		s_options,
		s_level,
		s_win,
		s_lose,
		s_quit
	};

	/*state variables*/


	//==================================================//

	/*Game entities variables*/
	sf::RenderWindow* window;
	sf::Event event;
	sf::Clock clock;
	sf::Sprite gameOverSprite;
	sf::Texture gameOverTexture;
	sf::SoundBuffer gameOverSoundBuffer;
	sf::Sound gameOverSound;
	bool gameOverSoundPlaying;
	float delta_time;
	float spawnTimer;
	float spawnTimerMax;
	Player* player;
	Framerate* frameRate;
	Math* math;


	//textures container for the game
	std::map<std::string, sf::Texture*> textures;
	std::vector<Bullet*> bullets;
	std::vector<SpaceRock*> spaceRocks;
	std::vector<Enemy*> enemies;

	/*Game entities variables*/

	//================================================//

	/*private funtions*/


private:

	void initWindow();
	void initTextures();
	void initSpaceRocks();
	void initEnemies();
	void initGameOverState();
	void createPlayer();
	void createFramerateInformation();
	void createMathSystem();

	Enemy* createEnemy(float posX, float posY);
	SpaceRock* createSpaceRock(float pos_x, float pos_y);


	/*private funtions*/



public:

	//public functions
	void update();
	void render();
	void run();
	void updatePollEvents();
	void updateInputs();
	void updateBullets();
	void updateSpaceRocks();
	void updateEnemies();
	void updateCombatOfEnemiesAndBullets();
	void updateCombatOfSpaceRocksAndBullets();
	const bool getGameOverStatus() const;


	//constructors/Destructors
	Game();
	~Game();

};

