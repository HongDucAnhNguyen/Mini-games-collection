#pragma once
#include <SFML/Graphics.hpp>
class Enemy
{

private:
	sf::Sprite enemySprite;
	sf::Texture enemyTexture;
	sf::Font font;
	sf::Text healthText;
	float shootingCooldown;
	float shootingCooldownMax;

	int hpMax;
	int hp;
	int points_gained_when_killed;
	int level;
	float enemySpeed;
	sf::RectangleShape boundingRect;



public:
	static sf::Texture enemyTextures[3];


private:

	void initTexture();
	void initSprite(float posX, float posY);
	void initFont();
	void initHealthText();




public:
	Enemy(int enemyLevel, float posX, float posY);
	~Enemy();

	void update(float directionX, float directionY);
	void render(sf::RenderWindow& window);
	void move(const float dirX, const float dirY);
	void moveDownRow();
	const int getEnemyPoints() const;
	const float getCurrentSpeed() const;
	const sf::FloatRect getBounds() const;
	const sf::FloatRect getHitBoxBounds() const;
	const sf::Vector2f getCurrentPos() const;
	bool enemyCanShoot();


	const int getHp() const;
	void setHp(int newHp);
	void increaseSpeed();

};

