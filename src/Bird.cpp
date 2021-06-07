#include "inc/Bird.hpp"
#include <SFML/Graphics/Rect.hpp>

// bird description

int birdData = 1;

Bird::Bird(){
	texture.loadFromFile("res/birds.png");
	sprite.setTexture(texture);
	sprite.setTextureRect(sf::IntRect(0,0,17,12));
	sprite.setScale(2.9,2.3);
}

void Bird::init(b2World *world, float density, float friction, float rest, float w, float h){
	def.type = b2_dynamicBody;
	def.bullet = true;
	def.gravityScale = 30;
	def.allowSleep = false;
	def.position.Set(175.f / PPM, 240 / PPM);
	
	body = world->CreateBody(&def);
	
	shape.SetAsBox(w / PPM, h / PPM);
	
	fixture.shape = &shape;
	fixture.density = density;
	fixture.friction = friction;
	fixture.restitution = rest;
	
	body->CreateFixture(&fixture);
	body->GetUserData().pointer = reinterpret_cast<uintptr_t>(&birdData);
	body->SetAwake(false);
}

void Bird::checkButton(sf::Event &event){
	if(!pr && event.type == sf::Event::KeyPressed)
		pr = true;
	
	if(pr && event.type == sf::Event::KeyReleased)
		bJump = true;
}

void Bird::jump(){
	if(bJump){
		body->SetLinearVelocity(b2Vec2(0, 0));
		body->ApplyLinearImpulse(b2Vec2(0, -1.5200), body->GetWorldCenter(), 1);
		bJump = false;
	}	
}

void Bird::follow(){
	sprite.setPosition(body->GetPosition().x * PPM - sprite.getGlobalBounds().width * 0.5f, body->GetPosition().y * PPM - sprite.getGlobalBounds().height * 0.5f);
	
	sprite.setRotation(body->GetAngle());
}

void Bird::checkVel(){
	b2Vec2 bodyVel = body->GetLinearVelocity();
	b2Vec2 maxVel(0, 15.5);
	
	if(bodyVel.Length()>maxVel.Length()){
		body->SetLinearVelocity(maxVel);
	}
	
	float bodyVelY = body->GetLinearVelocity().y;
	
	if(bodyVelY > 0){
		sprite.setRotation(sprite.getRotation() + bodyVelY * 2.5);
	}
	
	else{
		sprite.setRotation(sprite.getRotation() + bodyVelY * 1.5);
	}
}
void Bird::animation(){
	float time = clock.getElapsedTime().asMicroseconds();
	clock.restart();
	time = time/800;
	
	CurrentFrame += 0.008*time;
	if(CurrentFrame>=3)
		CurrentFrame-=3;
	sprite.setTextureRect(sf::IntRect(17*int(CurrentFrame)+CurrentFrame, 0, 17, 12));
}
void Bird::functions(){
	jump();
	follow();
	checkVel();
	animation();
}
