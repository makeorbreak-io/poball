#include "team.h"

#include <iostream>

Team::Team(int id){
    this->identifier = id;
    this->goalsScored = 0;
}

void Team::addPlayer(int id , Duck* player){
  this->mut->lock();
    this->players.insert(std::make_pair(id,player));
  this->mut->unlock();
}

void Team::draw(sf::RenderWindow *window){
  this->mut->lock();
    for (auto it = this->players.begin(); it != this->players.end(); it++ ){
      it->second->draw(window);
    }
  this->mut->unlock();
}
