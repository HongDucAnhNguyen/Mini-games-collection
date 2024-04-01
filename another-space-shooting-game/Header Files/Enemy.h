#pragma once
#include <SFML/Graphics.hpp>

class Enemy
{

private:
	sf::Sprite enemySprite;
	sf::Texture enemyTexture;
	sf::Font font;
	sf::Text healthText;



	int hpMax;
	int hp;
	int damage;
	int points_gained_when_killed;
	int level;
	float enemySpeed;
	sf::RectangleShape boundingRect;


public:



private:

	void initTexture();
	void initSprite(float posX, float posY);
	void initFont();
	void initHealthText();




public:
	Enemy(float posX, float posY);
	~Enemy();

	void update();
	void render(sf::RenderWindow& window);
	void move(const float dirX, const float dirY);

	const int getEnemyPoints() const;
	const float getCurrentSpeed() const;
	const sf::FloatRect getBounds() const;
	const sf::FloatRect getHitBoxBounds() const;
	const int getHp() const;
	void setHp(int newHp);

};

