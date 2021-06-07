#include "inc/Listener.hpp"

// listener description

void Listener::BeginContact(b2Contact *contact){
}
void Listener::EndContact(b2Contact *contact){
	b2Body *first = contact->GetFixtureA()->GetBody();
	b2Body *second = contact->GetFixtureB()->GetBody();
	if (first->GetUserData().pointer == reinterpret_cast<uintptr_t>(&birdData)){
		if (second->GetUserData().pointer == reinterpret_cast<uintptr_t>(&groundData)){
			bRestart = true;						
		}
	}
	if (first->GetUserData().pointer == reinterpret_cast<uintptr_t>(&birdData)){
		if (second->GetUserData().pointer == reinterpret_cast<uintptr_t>(&pillarData)){
			bRestart = true;
		}
	}
}
void Listener::PreSolve(b2Contact *contact,b2Manifold *manifold){
}       
void Listener::PostSolve(b2Contact *contact,b2ContactImpulse *impulse){
}
