#pragma once
#include <SFML/Graphics.hpp>


class SpaceRock
{


private:
	sf::CircleShape shape;

	unsigned speed;
	unsigned points_gained_when_killed;
	unsigned hp;
	unsigned hpMax;
	unsigned damage;
	unsigned randomVerticesFactor;





public:
	sf::RectangleShape boundingRect;


private:
	void initVariables();
	void initShape();

public:

	SpaceRock(float pos_x, float pos_y);
	~SpaceRock();
	void update();
	void render(sf::RenderWindow& window);
	const sf::FloatRect getBounds() const;
	const unsigned getSpaceRockPoints() const;
	const unsigned getSpaceRockHp() const;
	const unsigned getDamage() const;
	void setSpaceRockHp(unsigned hp);

};

