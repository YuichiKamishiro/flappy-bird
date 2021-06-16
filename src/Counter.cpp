#include "inc/Counter.hpp"
#include <iostream>

Counter::Counter(){
    insideFont.loadFromFile("res/inside.ttf");
    outsideFont.loadFromFile("res/outside.ttf");

    insideText.setFont(insideFont);
    outsideText.setFont(outsideFont);

    insideText.setCharacterSize(48);
    insideText.setPosition(180, 50);
    outsideText.setCharacterSize(48);
    outsideText.setPosition(180, 50);
    outsideText.setFillColor(sf::Color::Black);
}

void Counter::check(PillarsSpawner &ps, Bird &bird){
    for (int i = 0; i < ps.VectorOfPillars.size(); i++){
        if (bird.sprite.getPosition().x > ps.VectorOfPillars[i].firstSprite.getPosition().x && ps.VectorOfPillars[i].isChecked == false){
            score++;
            ps.VectorOfPillars[i].isChecked = true;
        }
    }

    fstr.open("res/record.txt", std::ios::in | std::ios::out);
    
	if(!fstr){
        std::cout<<"Error"<<std::endl;
    }

    int record;
    fstr >> record;

    fstr.close();

    if(score > record){

        fstr.open("res/record.txt", std::ios::in | std::ios::out | std::ios::trunc);

        if (!fstr){
            std::cout << "Error" << std::endl;
        }

        fstr << score;
        fstr.close();
    }
}

void Counter::update(){
    std::stringstream sstr;
    sstr << score;
    insideText.setString(sstr.str());
    outsideText.setString(sstr.str());
}
