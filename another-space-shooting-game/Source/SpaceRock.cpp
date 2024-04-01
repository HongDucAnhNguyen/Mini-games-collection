#include "../Header Files/SpaceRock.h"

void SpaceRock::initVariables()
{


	this->speed = rand() % 10 + 1;

	this->randomVerticesFactor = rand() % 20 + 3;
	this->hpMax = this->randomVerticesFactor * 10;
	this->hp = this->hpMax;
	this->damage = this->randomVerticesFactor;
	this->points_gained_when_killed = this->randomVerticesFactor;

	this->shape.setFillColor(sf::Color(
		//R
		rand() % 225 + 20,
		//G
		rand() % 255 + 1,
		//B
		rand() % 255 + 1,
		//Alpha
		255));
}

void SpaceRock::initShape()
{
	//random radius value between 20 and 39
	this->shape.setRadius(rand() % 20 + 20);

	this->shape.setPointCount(this->randomVerticesFactor);
	this->boundingRect.setFillColor(sf::Color::Transparent);
	this->boundingRect.setOutlineColor(sf::Color::Green);
	this->boundingRect.setOutlineThickness(1);


	this->boundingRect.setSize(sf::Vector2f
	(this->shape.getGlobalBounds().width, this->shape.getGlobalBounds().height));



}



SpaceRock::SpaceRock(float pos_x, float pos_y)
{
	this->initVariables();
	this->initShape();
	this->shape.setPosition(pos_x, pos_y);
	this->boundingRect.setPosition(this->shape.getPosition());


}

SpaceRock::~SpaceRock()
{
}

void SpaceRock::update()
{

	this->shape.move(0, 1 * this->speed);
	this->boundingRect.setPosition(this->shape.getPosition());

}

void SpaceRock::render(sf::RenderWindow& window)
{
	if (this->hp > 0) {
		window.draw(this->shape);
		window.draw(this->boundingRect);
	}
}

const sf::FloatRect SpaceRock::getBounds() const
{
	return this->shape.getGlobalBounds();
}

const unsigned SpaceRock::getSpaceRockPoints() const
{
	return this->points_gained_when_killed;
}

const unsigned SpaceRock::getSpaceRockHp() const
{
	return this->hp;
}

const unsigned SpaceRock::getDamage() const
{
	return this->damage;
}

void SpaceRock::setSpaceRockHp(unsigned hp_set)
{
	this->hp = hp_set;
}
