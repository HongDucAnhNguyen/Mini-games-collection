#include "../Header Files/Player.h"
#include <iostream>
void Player::initPlayer(sf::RenderWindow& window)
{

	this->playerSprite.setTexture(this->playerTexture);
	this->playerSprite.setTextureRect(sf::IntRect(0, 0, 392, 338));
	this->playerSprite.scale(0.2f, 0.2f);

	this->playerSprite.setPosition(window.getSize().x / 2, window.getSize().y - 100);

}

void Player::initFont()
{
	if (!this->font.loadFromFile("game_assets/fonts/arial.ttf")) {
		std::cout << "score font did not load" << std::endl;
	}
	else std::cout << "score font loaded" << std::endl;
}

void Player::initScoreText()
{
	this->scoreText.setPosition(10, 50);
	this->scoreText.setFont(font);
	this->scoreText.setString("SCORE: " + std::to_string(this->score));
	this->scoreText.setCharacterSize(16);

}

void Player::initHealthText()
{
	this->healthText.setPosition(this->playerSprite.getPosition() - sf::Vector2f(10, 10));
	this->healthText.setFont(font);
	this->healthText.setString(std::to_string(this->hp));
	this->healthText.setCharacterSize(16);
}





void Player::initTexture()
{

	if (!this->playerTexture.loadFromFile("game_assets/ship.png")) {

		std::cout << "Error loading texture" << std::endl;


	}
	else std::cout << "loaded player texture" << std::endl;


}

void Player::setScore(unsigned pointsReceived)
{
	this->score = pointsReceived;
}

const unsigned Player::getScore() const
{
	return this->score;
}

const unsigned Player::getDamage() const
{
	return this->damage;
}

const int Player::getHp() const
{
	return this->hp;
}

const sf::FloatRect Player::getBounds() const
{
	return this->playerSprite.getGlobalBounds();
}





Player::Player(sf::RenderWindow& window) : score(0), playerSpeed(PLAYER_SPEED), shootingCooldown(PLAYER_SHOOTING_COOLDOWN_MAX), shootingCooldownMax(PLAYER_SHOOTING_COOLDOWN_MAX), damage(PLAYER_DAMAGE), hpMax(PLAYER_MAX_HP), hp(PLAYER_MAX_HP)
{
	this->initTexture();
	this->initPlayer(window);
	this->initFont();
	this->initScoreText();
	this->initHealthText();

	this->playerHealthBar.setFillColor(sf::Color::Red);
	this->playerHealthBar.setSize(sf::Vector2f(this->hp, 20));
	this->playerHealthBar.setPosition(10, 80);
	this->playerHealthBarBackground.setFillColor(sf::Color(83, 83, 83));
	this->playerHealthBarBackground.setSize(sf::Vector2f(this->hpMax, 20));
	this->playerHealthBarBackground.setPosition(10, 80);

}

Player::~Player()
{
}

void Player::update()
{






	if (this->shootingCooldown < this->shootingCooldownMax) {
		this->shootingCooldown += 1;

	}


	this->scoreText.setString("SCORE: " + std::to_string(this->score));
	this->healthText.setPosition(this->playerHealthBar.getPosition() + sf::Vector2f(10, 0));
	this->healthText.setString("HP: " + std::to_string(this->hp));
	this->playerHealthBar.setSize(sf::Vector2f(this->hp, 20));

}

void Player::render(sf::RenderWindow& window)
{


	window.draw(this->playerSprite);
	window.draw(this->scoreText);
	window.draw(this->playerHealthBarBackground);
	window.draw(this->playerHealthBar);
	window.draw(this->healthText);



}

void Player::move(const float dirX, const float dirY)
{
	this->playerSprite.move(this->playerSpeed * dirX, 0);
}

const sf::Vector2f& Player::getCurrentPos() const
{
	return this->playerSprite.getPosition();
}

const float Player::getCurrentSpeed() const
{
	return this->playerSpeed;
}

bool Player::playerCanShoot()
{

	if (this->shootingCooldown >= this->shootingCooldownMax) {
		this->shootingCooldown = 0;
		return true;
	}
	else return false;
}

void Player::checkScreenCollision(sf::RenderWindow& window)
{
	if (this->playerSprite.getGlobalBounds().left < 0) {

		this->playerSprite.setPosition(0, this->playerSprite.getPosition().y);
	}


	if (this->playerSprite.getGlobalBounds().left
		+ this->playerSprite.getGlobalBounds().width > window.getSize().x) {

		this->playerSprite.setPosition(window.getSize().x - this->playerSprite.getGlobalBounds().width,
			this->playerSprite.getPosition().y);
	}





	if (this->playerSprite.getGlobalBounds().top < 0) {

		this->playerSprite.setPosition(this->playerSprite.getPosition().x,
			0
		);
	}


	if (this->playerSprite.getGlobalBounds().top
		+ this->playerSprite.getGlobalBounds().height > window.getSize().y) {

		this->playerSprite.setPosition(
			this->playerSprite.getPosition().x,
			window.getSize().y - this->playerSprite.getGlobalBounds().height);
	}
}

void Player::setCurrentPos(const sf::Vector2f& validPosition)
{
	this->playerSprite.setPosition(validPosition);
}

void Player::setHp(int hp_set)
{
	this->hp = hp_set;
}

