#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#define TIME_ELAPSED_MEASURE_THRESHOLD 200



class Framerate
{


private:
	sf::Text frameRateText;
	sf::Font font;
	float timerToMeasureFPS;


public:
	bool display;

public:
	Framerate();
	~Framerate();
	void initFramerateText();
	void initFramerateFont();
	void initFramerate();
	void update(float deltaTime);
	void render(sf::RenderWindow& window);

};

