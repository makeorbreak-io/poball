#include "team.h"
#include <iostream>

class Game
{
  private:
    Team team1;
    Team team2;
    bool finished;
    b2World *world;
    Duck* duck;
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
    }

  public:
    Game();
    void update();
};