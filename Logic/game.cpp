#include "game.h"

Game::Game()
{
    this->finished = false;
    this->team1 = Team(1);  
    this->team2 = Team(2);
    b2Vec2 Gravity(0.0f, 0.0f);
    this->world = new b2World(Gravity);
    this->duck = Duck(this->world,(float)0.0, (float)0.0, "assets/duck1.png");
    duck.resize(0.10,0.10);
    this->team1.addPlayer(1,this->duck);
}

void Game::update(){
    sf::RenderWindow window(sf::VideoMode(800, 600, 32), "P@oBall");
    window.setFramerateLimit(60);
    while (window.isOpen())
    {
        this->processMovement();
        window.clear(sf::Color::Black);
        this->team1.draw(&window);
        window.display();
        this->world->Step(1 / 60.f, 8, 3);
    }
}


