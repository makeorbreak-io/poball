#include <unordered_map>
#include "duck.h"

class Team{
    private:
        int identifier;
        std::unordered_map<int, Duck> players; //<id,Player>
        int goalsScored;
    public:
        Team();
        Team(int ident);
        void addPlayer(int id, Duck player);
        void draw(sf::RenderWindow *window);
};