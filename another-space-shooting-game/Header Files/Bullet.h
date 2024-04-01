#pragma once
#include <SFML/Graphics.hpp>




class Bullet
{

	sf::Sprite bulletSprite;

	sf::Vector2f direction;
	float bulletSpeed;


public:
	/*Bullet();*/
	Bullet(sf::Texture* texture, const sf::Vector2f& position, const sf::Vector2f& direction, float bulletSpeed);
	~Bullet();

	const sf::FloatRect getBounds() const;

	void update(float deltaTime);
	void render(sf::RenderWindow& window);
};

