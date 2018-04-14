#include "team.h"
#include <iostream>

class Game
{
  private:
    Team team1;
    Team team2;
    bool finished;
    b2World *world;
    Duck duck;
    void processMovement()
    {
        sf::Keyboard keyboard;
        if (keyboard.isKeyPressed(sf::Keyboard::Left))
        {
            std::cout << "Left" << std::endl;
            this->duck.move(-200.0, 0);
        }
        else if (keyboard.isKeyPressed(sf::Keyboard::Right))
        {
            std::cout << "Right" << std::endl;
            this->duck.move(200.0, 0);
        }
        else if (keyboard.isKeyPressed(sf::Keyboard::Up))
        {
            std::cout << "UP" << std::endl;
            this->duck.move(0, 200.0);
        }
        else if (keyboard.isKeyPressed(sf::Keyboard::Down))
        {
            std::cout << "Down" << std::endl;
            this->duck.move(0, -200.0);
        }
    }

  public:
    Game();
    void update();
};