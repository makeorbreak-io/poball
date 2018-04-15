#include "team.h"
#include <iostream>

Team::Team(){
    
}

Team::Team(int id){
    this->identifier = id;
    this->goalsScored = 0;
}

void Team::addPlayer(int id , Duck* player){
    this->players.insert(std::make_pair(id,player));
}

void Team::draw(sf::RenderWindow *window){
    for (auto it = this->players.begin(); it != this->players.end(); ++it ){
        it->second->draw(window);
    }
}

void Team::scoreGoal(){
	std::cout << "GOAL Team :" << this->identifier << " scored a GOAL. \n";
	this->goalsScored += 1;
}

void Team::resetGoal(){
	this->goalsScored = 0;
}

int Team::getGoalScored(){
	return this->goalsScored;
}

int Team::getId(){
	return this->identifier;
}