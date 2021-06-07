#pragma once
#include "All.hpp"
#include "Variables.hpp"

class Ground{
public:
    sf::Texture texture;
    sf::Sprite sprite; 

    b2Body *body;
    b2BodyDef def;
    b2PolygonShape shape;

    sf::Clock clock;
    float fMove = 0;
    
	Ground();
    void init(b2World *world);
    void checkPos();
};
