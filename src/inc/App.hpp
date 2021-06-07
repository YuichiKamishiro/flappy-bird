#pragma once
#include "All.hpp"
#include "Pillar.hpp"
#include "Listener.hpp"
#include "Counter.hpp"
#include "Bird.hpp"
#include "Ground.hpp"

class App{
public:	
	float delta = 0.f, time = 0.f, timeStep = 1.f / 60.f; 

	sf::Clock clock;

	bool bpr = false;

	sf::RenderWindow window;
	sf::Event event;
	sf::Texture texture;
	sf::Sprite background, inscription_help, inscription_name, spreadsheet, medal;
	
	sf::Font insideFont, outsideFont;
	sf::Text insideScoreText, insideBestText, outsideScoreText, outsideBestText;

	Bird bird;
	Ground ground;
	Listener listener;
	PillarsSpawner pillarsSpawner;
	Counter counter;

	void processEvent();
	void render();
	void display();
	void checkStart(sf::RenderWindow &window);
	void restart();
	bool wait();
	void run();

	App();
};
