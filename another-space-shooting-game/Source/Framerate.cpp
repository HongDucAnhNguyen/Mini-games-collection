#include "../Header Files/Framerate.h"

Framerate::Framerate() : timerToMeasureFPS(0), display(true)
{
	this->initFramerate();
}

Framerate::~Framerate()
{




}

void Framerate::initFramerateText()
{

	//set character size
	this->frameRateText.setCharacterSize(24);
	// set the color
	this->frameRateText.setFillColor(sf::Color::Yellow);

	// set the text style
	this->frameRateText.setStyle(sf::Text::Bold);

	this->frameRateText.setFont(this->font);
	this->frameRateText.setPosition(10, 10);


}

void Framerate::initFramerateFont()
{
	if (!this->font.loadFromFile("game_assets/fonts/arial.ttf")) {
		std::cout << "font did not load" << std::endl;
	}
	else std::cout << "font loaded" << std::endl;
}

void Framerate::initFramerate()
{
	this->initFramerateFont();
	this->initFramerateText();
}

void Framerate::update(float deltaTime)
{

	this->timerToMeasureFPS += deltaTime;

	//accumulate time elapsed since the last text rendered

	if (this->timerToMeasureFPS >= TIME_ELAPSED_MEASURE_THRESHOLD) {

		//print fps text on screen every 100ms

		int fps = 1000 / deltaTime;


		this->frameRateText.setString("FPS: " + std::to_string(fps));
		//reset to measure and render after the next 100ms had elapsed
		this->timerToMeasureFPS = 0;
	}
}

void Framerate::render(sf::RenderWindow& window)
{
	if (this->display) {
		window.draw(this->frameRateText);
	}
}


