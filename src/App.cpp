#include "inc/App.hpp"
#include <iostream>
bool bStart = true; // start state
bool bRestart = false; // restart state
int lastTime = 0;
void App::run(){
	srand(std::time(0)); //random seed
	
	b2Vec2 gravity(0,+1); // gravity
	b2World world(gravity);

	bird.init(&world, 0.1f, 0.f, 0.1f, 25.5f, 13.8f); //initialization 
	ground.init(&world);
	world.SetContactListener(&listener); //choose contact listener
	window.setFramerateLimit(130);
	while(window.isOpen()){
		processEvent(); // processing events

		delta = clock.getElapsedTime().asSeconds(); //delta
		clock.restart();
                        
		if(bRestart){ // check if Restart == true
			restart();
		}

		//functions
		bird.functions();
		ground.checkPos();
		counter.check(pillarsSpawner,bird);
		counter.update();
		pillarsSpawner.destroy(&world);

		if(bStart == false){ // check game state
			pillarsSpawner.spawn(delta, world,texture);
			pillarsSpawner.follow();
		}

		for (time += delta; time >= timeStep; time -= timeStep){ // world step
			world.Step(timeStep, 6, 2);
		}

		window.clear(); // clear,render,display
		render();
		display();
    }
}

// function description

App::App() : window(sf::VideoMode(420,600), "flappy-bird-demo"){
	
	outsideFont.loadFromFile("res/outside.ttf");
	insideFont.loadFromFile("res/inside.ttf");

	outsideScoreText.setFont(outsideFont);
	outsideBestText.setFont(outsideFont);

	insideScoreText.setFont(insideFont);
	insideBestText.setFont(insideFont);

	outsideScoreText.setCharacterSize(22);
	insideScoreText.setCharacterSize(22);

	outsideBestText.setCharacterSize(22);
	insideBestText.setCharacterSize(22);

	outsideScoreText.setFillColor(sf::Color::Black);
	outsideBestText.setFillColor(sf::Color::Black);


	texture.loadFromFile("res/tileset.png");

	spreadsheet.setTexture(texture);
	medal.setTexture(texture);
	inscription_name.setTexture(texture);
	inscription_help.setTexture(texture);
	background.setTexture(texture);

	spreadsheet.setTextureRect(sf::IntRect(146, 58, 114, 58));
	medal.setTextureRect(sf::IntRect(302, 138, 23, 23));
	background.setTextureRect(sf::IntRect(0, 0, 150, 245));
	inscription_name.setTextureRect(sf::IntRect(145, 172, 97, 23));
	inscription_help.setTextureRect(sf::IntRect(174, 122, 45, 50));

	inscription_name.setPosition(80, 0);
	inscription_help.setPosition(250, 200);
	medal.setPosition(80,250);
	spreadsheet.setPosition(45.6f,200);
	insideScoreText.setPosition(310, 240);
	outsideScoreText.setPosition(310, 240);
	insideBestText.setPosition(310, 290);
	outsideBestText.setPosition(310, 290);

	inscription_name.setScale(3, 2.3);
	inscription_help.setScale(3, 2.3);
	background.setScale(3, 2.3);
	spreadsheet.setScale(3, 2.3);
	medal.setScale(3, 2.3);
} 
void App::processEvent(){
    while(window.pollEvent(event)){
        if(event.type == sf::Event::Closed)
            window.close();
        bird.checkButton(event);
    }
}
void App::render(){
	window.draw(background);
	pillarsSpawner.renderPillars(window);
	window.draw(ground.sprite);
	
	if(!bRestart){
		window.draw(bird.sprite);
	}
	
	if(bpr && !bRestart){
		window.draw(counter.insideText);
		window.draw(counter.outsideText);
	}
	
	if(bRestart){
		window.draw(spreadsheet);
		window.draw(medal);
		window.draw(insideBestText);
		window.draw(outsideBestText);
		window.draw(insideScoreText);
		window.draw(outsideScoreText);
	}
	
	checkStart(window);
}
void App::display(){
    window.display();
}
void App::checkStart(sf::RenderWindow &window){
	if(!bpr && bird.pr == true){
		bird.body->SetAwake(true);
		bStart = false;
		bpr = true;
	}
	else if(!bpr && !bird.pr){
		bird.body->SetAwake(false);
		window.draw(inscription_name);
		window.draw(inscription_help);
	}
}
bool App::wait(){
	if(bird.bJump){
		return true;
	}
	
	else
		return false;
}
void App::restart(){
	if(counter.score < 10){
		medal.setTextureRect(sf::IntRect(0, 0, 0, 0));
	}
	
	else if(counter.score >= 10 && counter.score < 20){
		medal.setTextureRect(sf::IntRect(302, 137, 24, 24));
	}
	
	else if(counter.score >= 20 && counter.score < 30){
		medal.setTextureRect(sf::IntRect(266, 229, 24, 24));
	}
	
	else if(counter.score >= 30 && counter.score < 40){
		medal.setTextureRect(sf::IntRect(242, 229, 24, 24));
	}
	
	else if(counter.score >= 40){
		medal.setTextureRect(sf::IntRect(220, 144, 24, 24));
	}
	
	bird.body->SetTransform(b2Vec2(175.f / PPM, 240.f / PPM),0);
	bird.body->SetAwake(false);

	for(int i = 0;i < pillarsSpawner.VectorOfPillars.size();i++){
		pillarsSpawner.VectorOfPillars[i].destroy = true;
	}

	std::stringstream sstr;
	sstr<<counter.score;

	outsideScoreText.setString(sstr.str());
	insideScoreText.setString(sstr.str());

	int record;
	
	std::fstream ofstr;
	std::stringstream sstr2;

	ofstr.open("res/record.txt",std::ios::in | std::ios::out);

	ofstr>>record;
	sstr2<<record;

	insideBestText.setString(sstr2.str());
	outsideBestText.setString(sstr2.str());

	if(wait()){
		counter.score = 0;
		bpr = false;
		bird.pr = false;
		bStart = true;
		bRestart = false;
		pillarsSpawner.fSpawn = -2;
	}
}
