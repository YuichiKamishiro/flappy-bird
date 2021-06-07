#pragma once
#include "All.hpp"
#include "Variables.hpp"

class Bird{
public:
    bool bJump = 0, pr = false;

    sf::Texture texture;
    sf::Sprite sprite;

	sf::Clock clock;
	float CurrentFrame = 0;
    b2Body* body;
    b2BodyDef def;
    b2PolygonShape shape;
    b2FixtureDef fixture;

    Bird();
    void init(b2World* world, float density, float friction, float rest, float w, float h);
    void jump();
    void follow();
    void checkButton(sf::Event &event);
	void functions();
    void checkVel();
	void animation();
};
