#ifndef TEAM_H
#define TEAM_H

#include <unordered_map>
#include "duck.h"


class Team{
    private:
        sf::Mutex *mut = new sf::Mutex();
        int identifier;
        std::unordered_map<int, Duck*> players = std::unordered_map<int, Duck*>(); //<id,Player>
        int goalsScored;
    public:
        Team();
        Team(int ident);
        void addPlayer(int id, Duck* player);
        void draw(sf::RenderWindow *window);
};
<<<<<<< HEAD

#endif
=======
>>>>>>> b2535bb49206a9723bac1ac09288195a80c5ab4a
