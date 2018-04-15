#ifndef GAME_H
#define GAME_H

#include "team.h"
#include "ball.h"
#include "barrier.h"
#include "goalside.h"
#include "colision_callback.h"
#include <iostream>

class MyContactListener;
class Goalside;
class Game {
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
    sf::RenderWindow *window;
    sf::Text score;
    sf::Font font;
    

    Team *checkWinning();
    void resetGoal();
    void processMovement();
    void handleReset();
    void won(int id);

  public:
    Game();
    void update();


};

#endif