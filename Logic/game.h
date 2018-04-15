#ifndef GAME_H
#define GAME_H

#include "team.h"
#include "ball.h"
#include "barrier.h"
#include "goalside.h"
#include "colision_callback.h"
#include <iostream>

class Game
{
  private:
    Team team1;
    Team team2;
    bool finished;
    b2World *world;
    Duck* duck;
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

  public:
    Game();
    void update();
};

#endif