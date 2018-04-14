#include "team.h"

Team::Team(){
    
}

Team::Team(int id){
    this->identifier = id;
    this->goalsScored = 0;
}

void Team::addPlayer(int id , Duck player){
    this->players.insert(std::make_pair(id,player));
}