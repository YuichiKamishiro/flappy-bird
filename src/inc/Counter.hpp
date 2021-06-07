#pragma once
#include "All.hpp"
#include "Pillar.hpp"
class Counter{
public:
    std::fstream fstr;
    std::stringstream sstr;

    sf::Font insideFont, outsideFont;
    sf::Text insideText, outsideText;

    int score = 0;
    
	Counter();
    void check(PillarsSpawner &ps, Bird &bir);
    void update();
};
