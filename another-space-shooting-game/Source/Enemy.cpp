#include "../Header Files/Enemy.h"
#include <iostream>


sf::Texture Enemy::enemyTextures[3] = {};


void Enemy::initTexture()
{


	if (!enemyTextures[0].getSize().x) {
		if (enemyTextures[0].loadFromFile("game_assets/enemy pack/enemy_lvl1.png"))
			std::cout << "Loaded enemy texture for level 1" << std::endl;
		else
			std::cerr << "Failed to load enemy texture for level 1" << std::endl;
	}

	if (!enemyTextures[1].getSize().x) {
		if (enemyTextures[1].loadFromFile("game_assets/enemy pack/enemy_lvl2.png"))
			std::cout << "Loaded enemy texture for level 2" << std::endl;
		else
			std::cerr << "Failed to load enemy texture for level 2" << std::endl;
	}

	if (!enemyTextures[2].getSize().x) {
		if (enemyTextures[2].loadFromFile("game_assets/enemy pack/enemy_lvl3.png"))
			std::cout << "Loaded enemy texture for level 3" << std::endl;
		else
			std::cerr << "Failed to load enemy texture for level 3" << std::endl;
	}









}

void Enemy::initSprite(float posX, float posY)
{

	switch (this->level) {

	case 1:
		this->enemySprite.setTexture(this->enemyTextures[0]);

		break;

	case 2:
		this->enemySprite.setTexture(this->enemyTextures[1]);
		break;

	case 3:
		this->enemySprite.setTexture(this->enemyTextures[2]);
		break;

	default:
		this->enemySprite.setTexture(this->enemyTextures[0]);
		break;

	}


	this->enemySprite.setTextureRect(sf::IntRect(0, 0, 40, 32));

	this->enemySprite.setPosition(posX, posY);


	this->boundingRect.setFillColor(sf::Color::Transparent);

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



Enemy::Enemy(int enemyLevel, float posX, float posY) : level(0), enemySpeed(.4)
{
	this->level = enemyLevel;
	if (this->level == 1) {
		this->hp = 30;
		this->hpMax = 30;
		this->points_gained_when_killed = 10;
	}
	if (this->level == 2) {
		this->hp = 60;
		this->hpMax = 60;
		this->points_gained_when_killed = 40;
	}
	if (this->level == 3) {
		this->hp = 120;
		this->hpMax = 120;
		this->points_gained_when_killed = 100;
	}
	this->initTexture();
	this->initSprite(posX, posY);
	this->initFont();
	this->initHealthText();
}




Enemy::~Enemy()
{


}



void Enemy::update(float directionX, float directionY)
{





	if (this->hp > 0) {


		if (this->shootingCooldown < this->shootingCooldownMax) {
			this->shootingCooldown += 1;

		}



		this->boundingRect.setPosition(this->enemySprite.getPosition().x + 15, this->enemySprite.getPosition().y + 15);
		this->boundingRect.setOutlineColor(sf::Color::Red);
		this->healthText.setPosition(this->enemySprite.getPosition() - sf::Vector2f(10, 10));
		this->healthText.setString(std::to_string(this->hp));

		this->move(directionX, directionY);
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
	this->enemySprite.move(this->enemySpeed * dirX,
		this->enemySpeed * dirY);
}

void Enemy::moveDownRow()
{

	this->enemySprite.setPosition(sf::Vector2f(this->enemySprite.getPosition().x,

		this->enemySprite.getPosition().y + 5));

	this->increaseSpeed();

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

const sf::Vector2f Enemy::getCurrentPos() const
{
	return this->enemySprite.getPosition();
}

bool Enemy::enemyCanShoot()
{
	if (this->shootingCooldown >= this->shootingCooldownMax) {

		this->shootingCooldown = 0;
		return true;
	}
	return false;
}

const int Enemy::getHp() const
{
	return this->hp;
}

void Enemy::setHp(int newHp)
{
	this->hp = newHp;
}

void Enemy::increaseSpeed()
{
	this->enemySpeed += .1f;
}
