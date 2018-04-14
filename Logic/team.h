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
