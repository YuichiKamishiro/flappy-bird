#include "inc/Ground.hpp"

int groundData = 2;

Ground::Ground(){
    texture.loadFromFile("res/ground.png");
    sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect(0, 0, 300, 60));
    sprite.setScale(3, 2.3);
    sprite.setPosition(0, 481.5f);
}

void Ground::init(b2World *world){
    def.position.Set(450.f / PPM, 481.5f / PPM);
    body = world->CreateBody(&def);
    shape.SetAsBox(450.f / PPM, 0.1f / PPM);
    body->CreateFixture(&shape, 0.f);
    body->GetUserData().pointer = reinterpret_cast<uintptr_t>(&groundData);
}

void Ground::checkPos(){
    float time = clock.getElapsedTime().asMicroseconds();
    clock.restart();

    fMove += 0.1 * time;
    if(fMove >=1){
        sprite.move(-1.5f, 0);
    } 

    if(sprite.getPosition().x <= -450){
        sprite.setPosition(0, 481.5f);
    }
}
