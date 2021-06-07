#pragma once                                                  
#include "All.hpp"               
#include "Variables.hpp"

class Listener : public b2ContactListener{                    
public:                                                       
    void BeginContact(b2Contact *contact);                        
    void EndContact(b2Contact *contact);                          
    void PreSolve(b2Contact *contact,b2Manifold *manifold);       
    void PostSolve(b2Contact *contact,b2ContactImpulse *impulse); 
};                                                            
                                                              

