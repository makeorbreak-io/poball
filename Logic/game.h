#include "team.h"

class Game{
    private:
        Team team1;
        Team team2;
        bool finished;
        b2World * world;
    public:
        Game();  
        void update();
};