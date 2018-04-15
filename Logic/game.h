#ifndef GAME_H
#define GAME_H

#include "team.h"
<<<<<<< HEAD
#include "ball.h"
#include "barrier.h"
#include "goalside.h"
#include "colision_callback.h"
=======
#include "../network/client.h"
>>>>>>> b2535bb49206a9723bac1ac09288195a80c5ab4a
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
<<<<<<< HEAD
    Ball* ball;
    MyContactListener *contactListener;
    sf::Sprite background;
    Goalside* goalside;
    Goalside* goalside2;
    Barrier* barriertop;
    Barrier* barrierbottom;
    Barrier* barrierleft;
    Barrier* barrierright;
    float sizeX,sizeY;
    void processMovement()
    {
        sf::Keyboard keyboard;
        if (keyboard.isKeyPressed(sf::Keyboard::Left))
        {
            this->duck->move(-5.0, 0);
        }
        else if (keyboard.isKeyPressed(sf::Keyboard::Right))
        {
            this->duck->move(5.0, 0);
        }
        if (keyboard.isKeyPressed(sf::Keyboard::Up))
        {
            this->duck->move(0, -5.0);
        }
        else if (keyboard.isKeyPressed(sf::Keyboard::Down))
        {
            this->duck->move(0, 5.0);
        }
        if(keyboard.isKeyPressed(sf::Keyboard::X)){
            this->ball->shootBall();
        }
    }
=======
    int my_id;
    std::unordered_map<int, Duck *> players;
>>>>>>> b2535bb49206a9723bac1ac09288195a80c5ab4a


    void processMovement();

    void updateState(std::istringstream &stream);

    void addPlayer(std::istringstream &stream);

    void newPlayer(int player_id, Duck *new_duck);
  public:
    Game();
    void update();
<<<<<<< HEAD
};

#endif
=======
    void static serverListener();
};
>>>>>>> b2535bb49206a9723bac1ac09288195a80c5ab4a
