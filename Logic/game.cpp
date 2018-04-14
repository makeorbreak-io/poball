#include "game.h"

Game::Game()
{
    this->finished = false;
    this->team1 = Team(1);  
    this->team2 = Team(2);
    b2Vec2 Gravity(0.0f, 0.0f);
    this->world = new b2World(Gravity);
    this->duck = new Duck(this->world,(float)0.0, (float)0.0, "assets/duck1.png");
    Duck * duck2 = new Duck(this->world,(float)400.0, (float)200.0, "assets/duck2.png");
    this->ball = new Ball(this->world, 800, 400, "assets/ball.png");
    this->team1.addPlayer(1,this->duck);
    this->team1.addPlayer(2,duck2);
    this->contactListener = new MyContactListener();
    this->world->SetContactListener(this->contactListener);
}

void Game::update(){
    sf::RenderWindow window(sf::VideoMode(1280, 760, 32), "P@oBall");
    window.setFramerateLimit(60);
    while (window.isOpen())
    {
        this->processMovement();
        window.clear(sf::Color::Black);
        this->team1.draw(&window);
        this->ball->draw(&window);
        window.display();
        this->world->Step(1 / 60.f, 8, 3);
    }
}


