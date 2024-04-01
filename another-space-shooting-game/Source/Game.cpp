#include "../Header Files/Game.h"
#include <iostream>






/*=====================================GAME UPDATES=====================================*/
/*Game entities creation*/
void Game::createPlayer()
{
	this->player = new Player(*(this->window));
}
Enemy* Game::createEnemy(float posX, float posY)
{
	return new Enemy(posX, posY);
}

void Game::createFramerateInformation() {

	this->frameRate = new Framerate();
}
void Game::createMathSystem() {
	this->math = new Math();
}

SpaceRock* Game::createSpaceRock(float pos_x, float pos_y) {
	return new SpaceRock(pos_x, pos_y);
}

/*Game entities creation*/


void Game::initWindow()
{
	this->window = new sf::RenderWindow(sf::VideoMode(800, 800), "another space shooting game");
	this->window->setFramerateLimit(60);
	this->window->setVerticalSyncEnabled(false);




}
void Game::initTextures()
{
	this->textures["BULLET"] = new sf::Texture();
	if (this->textures["BULLET"]->loadFromFile("game_assets/bullet.png")) {

		std::cout << "loaded bullet texture" << std::endl;
	}
	else std::cout << "cannot load bullet texture" << std::endl;








}

void Game::initSpaceRocks()
{
	this->spawnTimerMax = 1000;
	this->spawnTimer = this->spawnTimerMax;
}

void Game::initEnemies() {



	for (int i = 0; i < 8; i++) {
		if (i == 0) {
			this->enemies.push_back(this->createEnemy(10, 300));
		}
		else {

			float posX = this->enemies[i - 1]->getBounds().left + this->enemies[i - 1]->getBounds().width + 30;
			this->enemies.push_back(this->createEnemy(
				posX,
				300));
		}

	}
}




void Game::initGameOverState() {

	this->gameOverSoundBuffer.loadFromFile("game_assets/game_over_bad_chest.wav");
	this->gameOverSound.setBuffer(this->gameOverSoundBuffer);





	this->gameOverTexture.loadFromFile("game_assets/game over.png");
	this->gameOverSprite.setTexture(this->gameOverTexture);

	this->gameOverSprite.setTextureRect(sf::IntRect(0, 0, this->window->getSize().x, this->window->getSize().y));



}



const bool Game::getGameOverStatus() const {
	return this->currentState == game_state::s_lose;
}
/*=====================================GAME INITS=====================================*/








/*=====================================GAME CONSTRUCTOR/DESTRUCTOR=====================================*/
Game::Game() : window(nullptr), delta_time(0), player(nullptr),
frameRate(nullptr), math(nullptr), gameOverSoundPlaying(false)
{



	this->initWindow();
	this->initTextures();
	this->createPlayer();
	this->createFramerateInformation();
	this->createMathSystem();
	this->initSpaceRocks();
	this->initEnemies();
	this->initGameOverState();

}

Game::~Game()
{
	delete this->window;
	delete this->player;


	delete this->frameRate;
	delete this->math;

	//delete textures
	for (auto& i : this->textures) {

		//i first is the key, i second is the val
		delete i.second;
	}

	//delete bullets
	for (auto* i : this->bullets) {

		delete i;
	}
	//delete space rocks
	for (auto* i : this->spaceRocks) {

		delete i;
	}
	//delete enemies
	for (auto* i : this->enemies) {
		delete i;
	}
}
/*=====================================GAME INITS=====================================*/














/*=====================================GAME UPDATES=====================================*/

void Game::updatePollEvents()
{

	while (this->window->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			this->window->close();


		if (event.type == sf::Event::KeyPressed && event.Event::key.code == sf::Keyboard::Escape)
			this->window->close();

		if (event.type == sf::Event::KeyPressed && event.Event::key.code == sf::Keyboard::Q)
			this->frameRate->display = !this->frameRate->display;
	}
}

void Game::updateInputs()
{



	for (int i = 0; i < this->spaceRocks.size(); i++) {

		if (this->math->checkAABBCollision(this->player->getBounds(), this->spaceRocks[i]->getBounds())) {
			this->player->setHp(this->player->getHp() - this->spaceRocks[i]->getDamage());
			this->player->setScore(this->player->getScore() + this->spaceRocks[i]->getSpaceRockPoints());


			delete this->spaceRocks.at(i);
			this->spaceRocks.erase(this->spaceRocks.begin() + i);


		}
	}





	this->player->checkScreenCollision(*(this->window));


	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {

		this->player->move(-1 * this->player->getCurrentSpeed() * delta_time, 0);


	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {

		this->player->move(1 * this->player->getCurrentSpeed() * delta_time, 0);


	}


	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->player->playerCanShoot()) {






		this->bullets.push_back(
			new Bullet(this->textures["BULLET"], this->player->getCurrentPos(), sf::Vector2f(0, -1), .5)
		);




	}
}
void Game::updateBullets() {
	for (int index_offset = this->bullets.size() - 1; index_offset >= 0; index_offset--) {
		if (this->bullets[index_offset]->getBounds().top + this->bullets[index_offset]->getBounds().height < 0) {

			delete this->bullets.at(index_offset);

			this->bullets.erase(this->bullets.begin() + index_offset);

			std::cout << "deleted bullet" << std::endl;


		}
		else {
			this->bullets[index_offset]->update(this->delta_time);
		}
		//move the bullet
	}
}
void Game::updateSpaceRocks() {
	this->spawnTimer += this->delta_time;
	if (this->spawnTimer >= this->spawnTimerMax) {
		this->spaceRocks.push_back(
			this->createSpaceRock(rand() % this->window->getSize().x - 20, -100));
		this->spawnTimer = 0;

	}
	else {
		for (int i = this->spaceRocks.size() - 1; i >= 0; i--) {
			this->spaceRocks[i]->update();
		}
	}
}

void Game::updateEnemies() {
	for (int i = this->enemies.size() - 1; i >= 0; i--)
	{
		if (this->enemies[i]->getHp() > 0) {
			this->enemies[i]->update();

		}
	}
}


void Game::updateCombatOfEnemiesAndBullets()
{



	for (int i = this->enemies.size() - 1; i >= 0; i--) {







		for (int index_offset = this->bullets.size() - 1; index_offset >= 0; index_offset--) {





			if (math->checkAABBCollision(this->bullets[index_offset]->getBounds(),
				this->enemies[i]->getHitBoxBounds())) {



				if (this->enemies[i]->getHp() <= 0) {
					this->enemies[i]->setHp(0);
					this->player->setScore(this->player->getScore() + this->enemies[i]->getEnemyPoints());
					delete this->enemies.at(i);
					this->enemies.erase(this->enemies.begin() + i);
				}



				else {
					this->enemies[i]->setHp(this->enemies[i]->getHp() - this->player->getDamage());
				}

				delete this->bullets.at(index_offset);

				this->bullets.erase(this->bullets.begin() + index_offset);

				std::cout << "deleted bullet" << std::endl;

			}

		}













	}




}





void Game::updateCombatOfSpaceRocksAndBullets()
{




	for (int i = this->spaceRocks.size() - 1; i >= 0; i--) {



		if (this->spaceRocks[i]->getBounds().top > this->window->getSize().y) {

			delete this->spaceRocks.at(i);
			this->spaceRocks.erase(this->spaceRocks.begin() + i);
		}

		for (int k = this->bullets.size() - 1; k >= 0; k--) {







			if (math->checkAABBCollision(this->bullets[k]->getBounds(),
				this->spaceRocks[i]->getBounds()
			)) {
				if (this->spaceRocks[i]->getSpaceRockHp() <= 0) {
					this->spaceRocks[i]->setSpaceRockHp(0);


					this->player->setScore(this->player->getScore() +
						this->spaceRocks[i]->getSpaceRockPoints());

					delete this->spaceRocks.at(i);
					this->spaceRocks.erase(this->spaceRocks.begin() + i);

				}
				else {
					this->spaceRocks[i]->setSpaceRockHp(this->spaceRocks[i]->getSpaceRockHp() - this->player->getDamage());
				}

				delete this->bullets.at(k);

				this->bullets.erase(this->bullets.begin() + k);

			}

		}


	}


}









void Game::update()
{





	this->updatePollEvents();





	if (this->player->getHp() <= 0) {

		this->currentState = game_state::s_lose;
	}





	if (this->getGameOverStatus() == false) {



		this->updateInputs();






		this->frameRate->update(this->delta_time);
		if (this->player->getHp() > 0) { this->player->update(); }



		this->updateSpaceRocks();
		this->updateEnemies();
		this->updateCombatOfEnemiesAndBullets();
		this->updateCombatOfSpaceRocksAndBullets();
		this->updateBullets();

	}










}
/*=====================================GAME UPDATES=====================================*/








/*=====================================GAME RENDERS=====================================*/

void Game::render()
{


	this->window->clear();

	if (this->getGameOverStatus() == false) {

		this->player->render(*(this->window));


		for (auto* enemy : this->enemies) {

			enemy->render(*(this->window));


		}


		for (auto* spaceRock : this->spaceRocks) {
			spaceRock->render(*(this->window));

		}
		for (auto* bullet : this->bullets) {

			bullet->render(*(this->window));
		}

		this->frameRate->render(*(this->window));
	}

	else {

		if (this->gameOverSoundPlaying == false) {

			this->gameOverSound.play();
			this->gameOverSoundPlaying = true;

		}
		this->window->draw(this->gameOverSprite);

	}



	this->window->display();




}
/*=====================================GAME RENDERS=====================================*/




/*=====================================GAME RUNS=====================================*/

void Game::run()
{


	while (this->window->isOpen())
	{

		this->delta_time = this->clock.restart().asSeconds() * 1000;

		this->update();
		this->render();
	}
}
/*=====================================GAME UPDATES=====================================*/
