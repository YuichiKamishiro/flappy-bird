#include "inc/Pillar.hpp"

int pillarData = 3;

Pillar::Pillar(sf::Texture &texture){
    firstSprite.setTexture(texture);
    secondSprite.setTexture(texture);
    firstSprite.setTextureRect(sf::IntRect(303, 0, 26, 136));
    secondSprite.setTextureRect(sf::IntRect(330, 0, 26, 136));
	firstSprite.setScale(3.f, 2.3f);
	firstSprite.setOrigin(13.0f, 68.0f);
	secondSprite.setScale(3.f, 2.3f);
	secondSprite.setOrigin(13.0f, 68.0f);
}

void Pillar::init(b2World *world){
    firstDef.type=b2_kinematicBody;
    secondDef.type=b2_kinematicBody;
    float fY = rand()% 156 + 0;
	float sY = fY + 312 + 115;
    firstDef.position.Set(500.f / PPM , fY / PPM);
    secondDef.position.Set(500.f / PPM, sY / PPM);
    firstBody = world->CreateBody(&firstDef);
    secondBody = world->CreateBody(&secondDef);
    shape.SetAsBox(39.f / PPM, 156.4f / PPM);
    firstBody->CreateFixture(&shape, 1.f);
    secondBody->CreateFixture(&shape, 1.f);
	firstBody->SetLinearVelocity( b2Vec2(-7.0, 0 ) );
	secondBody->SetLinearVelocity( b2Vec2(-7.0, 0 ) );
    firstBody->GetUserData().pointer = reinterpret_cast<uintptr_t>(&pillarData);
    secondBody->GetUserData().pointer = reinterpret_cast<uintptr_t>(&pillarData);
}

 

void PillarsSpawner::follow(){
    for (int i = 0; i < VectorOfPillars.size(); ++i){
        VectorOfPillars[i].firstSprite.setPosition(VectorOfPillars[i].firstBody->GetPosition().x * PPM, VectorOfPillars[i].firstBody->GetPosition().y * PPM);
        VectorOfPillars[i].secondSprite.setPosition(VectorOfPillars[i].secondBody->GetPosition().x * PPM, VectorOfPillars[i].secondBody->GetPosition().y * PPM);
    }
}

void PillarsSpawner::renderPillars(sf::RenderWindow &window){
    for(int i = 0;i < VectorOfPillars.size();++i){
        window.draw(VectorOfPillars[i].firstSprite);
        window.draw(VectorOfPillars[i].secondSprite);
    }
}
void PillarsSpawner::spawn(float time, b2World &world, sf::Texture &texture){
    fSpawn += time;
    if (fSpawn >= 1.5){
        fSpawn = 0;
        Pillar pillar(texture);
        pillar.init(&world);
        VectorOfPillars.push_back(pillar);
    }
}
void PillarsSpawner::destroy(b2World *world){
	for(int i = 0;i < VectorOfPillars.size();i++){
		if (VectorOfPillars[i].firstSprite.getPosition().x <= -30)
            VectorOfPillars[i].destroy = true;
        
		if(VectorOfPillars[i].destroy){
			std::vector<Pillar>::iterator it = VectorOfPillars.begin();
			int x = 0;
			
			while(x != i){
				x++;
				*it++;
			}
			
			world->DestroyBody(VectorOfPillars[i].firstBody);
			world->DestroyBody(VectorOfPillars[i].secondBody);
			VectorOfPillars.erase(it);
		}
	}
}
