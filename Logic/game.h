#include "team.h"
#include "../network/client.h"
#include <iostream>
#include <sstream>
#include <unordered_map>

class Game
{
  private:
    static Game *instance;
    static sf::Mutex *mut;
    Client *socket = new Client(8001, "127.0.0.1");
    Team team1 = Team(0);
    Team team2 = Team(1);
    bool finished;
    b2World *world;
    Duck* duck;
    int my_id;
    std::unordered_map<int, Duck *> players;


    void processMovement();

    void updateState(std::istringstream &stream);

    void addPlayer(std::istringstream &stream);

    void newPlayer(int player_id, Duck *new_duck);
  public:
    Game();
    void update();
    void static serverListener();
};
