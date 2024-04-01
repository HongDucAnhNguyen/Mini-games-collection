#pragma once
#include <SFML/Graphics.hpp>


#define PLAYER_MAX_HP 200
#define PLAYER_DAMAGE 10
#define PLAYER_SHOOTING_COOLDOWN_MAX 20
#define PLAYER_SPEED .5f


class Player
{

private:
	sf::Sprite playerSprite;
	sf::RectangleShape playerHealthBar;
	sf::RectangleShape playerHealthBarBackground;
	sf::Texture playerTexture;
	float playerSpeed;

	float shootingCooldown;
	float shootingCooldownMax;
	sf::Font font;
	sf::Text scoreText;
	sf::Text healthText;
	unsigned score;
	int hp;
	int hpMax;

	unsigned damage;

private:

	void initPlayer(sf::RenderWindow& window);
	void initFont();
	void initScoreText();
	void initHealthText();
	void initTexture();




public:
	Player(sf::RenderWindow& window);
	~Player();




	void update();
	void render(sf::RenderWindow& window);
	void move(const float dirX, const float dirY);
	const sf::Vector2f& getCurrentPos() const;
	const float getCurrentSpeed() const;
	void setScore(unsigned pointsReceived);
	const unsigned getScore() const;
	const unsigned getDamage() const;
	const int getHp() const;
	const sf::FloatRect getBounds() const;
	bool playerCanShoot();
	void checkScreenCollision(sf::RenderWindow& window);
	void setCurrentPos(const sf::Vector2f& validPosition);
	void setHp(int hp_set);


};

