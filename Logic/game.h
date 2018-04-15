#ifndef GAME_H
#define GAME_H

#include "ball.h"
#include "barrier.h"
#include "goalside.h"
#include "colision_callback.h"
#include "duck.h"
#include <iostream>

class MyContactListener;
class Goalside;
class Game {
  private:
    bool finished;
    b2World *world;
    Duck* duck;
    Duck* duck2;
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
    sf::RenderWindow *window;
    sf::Text score;
    sf::Font font;
    

    Duck *checkWinning();
    void resetGoal();
    void processMovement();
    void handleReset();
    void won(int id);

  public:
    Game();
    void update();
    Ball * getBall();
    Duck * getDuck();
};

#endif