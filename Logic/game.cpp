#include "game.h"

Game::Game()
{
    this->finished = false;
    this->team1 = Team(1);
    this->team2 = Team(2);
    b2Vec2 Gravity(0.0f, 0.0f);
    this->world = new b2World(Gravity);
}

void Game::update(){
    sf::RenderWindow window(sf::VideoMode(800, 600, 32), "P@oBall");
    window.setFramerateLimit(60);
    sf::Event event;
    while (window.isOpen())
    {
        window.display();
        this->world->Step(1 / 60.f, 8, 3);
    }
}
