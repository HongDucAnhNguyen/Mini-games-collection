#include "../Header Files/Enemy.h"
#include <iostream>

void Enemy::initTexture()
{
	if (this->enemyTexture.loadFromFile("game_assets/enemy pack/enemy_lvl1.png")) {

		std::cout << "loaded enemy texture" << std::endl;

	}
	else std::cout << "cannot load enemy texture" << std::endl;
}

void Enemy::initSprite(float posX, float posY)
{
	this->enemySprite.setTexture(this->enemyTexture);
	this->enemySprite.setTextureRect(sf::IntRect(0, 0, 219, 243));
	this->enemySprite.scale(.2f, .2f);
	this->enemySprite.setPosition(posX, posY);


	this->boundingRect.setFillColor(sf::Color::Transparent);
	this->boundingRect.setOutlineColor(sf::Color::Red);
	this->boundingRect.setOutlineThickness(1);
	this->boundingRect.setSize(sf::Vector2f(
		this->enemySprite.getGlobalBounds().width - 30,
		this->enemySprite.getGlobalBounds().height - 30));

	this->boundingRect.setPosition(this->enemySprite.getPosition().x + 15, this->enemySprite.getPosition().y + 15);
}

void Enemy::initFont()
{
	if (!this->font.loadFromFile("game_assets/fonts/arial.ttf")) {
		std::cout << "font did not load" << std::endl;
	}
	else std::cout << "font loaded" << std::endl;
}

void Enemy::initHealthText()
{
	this->healthText.setPosition(this->enemySprite.getPosition() - sf::Vector2f(10, 10));
	this->healthText.setFont(font);
	this->healthText.setString(std::to_string(this->hp));
	this->healthText.setCharacterSize(16);
}

const float Enemy::getCurrentSpeed() const
{
	return this->enemySpeed;
}



Enemy::Enemy(float posX, float posY) : level(0), enemySpeed(.4), hpMax(100),
hp(100),
damage(5),
points_gained_when_killed(10)
{
	this->initTexture();
	this->initSprite(posX, posY);
	this->initFont();
	this->initHealthText();
}




Enemy::~Enemy()
{
}



void Enemy::update()
{





	if (this->hp > 0) {

		this->boundingRect.setPosition(this->enemySprite.getPosition().x + 15, this->enemySprite.getPosition().y + 15);
		this->boundingRect.setOutlineColor(sf::Color::Red);
		this->healthText.setPosition(this->enemySprite.getPosition() - sf::Vector2f(10, 10));
		this->healthText.setString(std::to_string(this->hp));
		//this->move(0, 1);
	}


}

void Enemy::render(sf::RenderWindow& window)
{
	if (this->hp > 0) {
		window.draw(this->enemySprite);
		window.draw(this->boundingRect);
		window.draw(this->healthText);
	}
}

void Enemy::move(const float dirX, const float dirY)
{
	//this->enemySprite.move(this->enemySpeed * dirX, this->enemySpeed * dirY);

}

const int Enemy::getEnemyPoints() const
{
	return this->points_gained_when_killed;
}

const sf::FloatRect Enemy::getBounds() const
{
	return this->enemySprite.getGlobalBounds();
}

const sf::FloatRect Enemy::getHitBoxBounds() const
{
	return this->boundingRect.getGlobalBounds();
}

const int Enemy::getHp() const
{
	return this->hp;
}

void Enemy::setHp(int newHp)
{
	this->hp = newHp;
}
