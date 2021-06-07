#pragma once
#include "All.hpp"
#include "Variables.hpp"
#include "Bird.hpp"
class PillarsSpawner;

class Pillar{
public:
    sf::Sprite firstSprite,secondSprite;
    sf::Texture texture;

    b2Body* firstBody;
    b2Body* secondBody;
    b2BodyDef firstDef,secondDef;
    b2PolygonShape shape;

    bool isChecked = false;
    bool destroy = false;

    Pillar(sf::Texture &texture);
    void init(b2World *world);
};
class PillarsSpawner{
public:
    std::vector<Pillar> VectorOfPillars;
   
   	float fSpawn = -2.f; 
   
   	void spawn(float time, b2World &world, sf::Texture &texture);
    void init(b2World *world);
    void follow();
	void destroy(b2World *world);
    void renderPillars(sf::RenderWindow &window);
};
