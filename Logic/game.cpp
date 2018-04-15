#include "game.h"

Game::Game()
{
    b2Vec2 Gravity(0.0f, 0.0f);
    this->world = new b2World(Gravity);
    this->contactListener = new MyContactListener();
    this->world->SetContactListener(this->contactListener);

    sf::Image image;

    image.loadFromFile("assets/pool.png");
    sf::Texture *texture = new sf::Texture();

    texture->loadFromImage(image);

    this->background.setTexture(*texture, true);

    this->barriertop = new Barrier(this->world, 0, 0, "assets/horizontal.png");
    this->barrierleft = new Barrier(this->world, 0, 0, "assets/vertical.png");
    this->barrierright = new Barrier(this->world, 0, 0, "assets/vertical.png");
    this->sizeY = this->background.getTexture()->getSize().y + 2.0f*this->barriertop->getSprite().getTexture()->getSize().y;

    this->sizeX = this->background.getTexture()->getSize().x + 2.0*this->barrierleft->getSprite().getTexture()->getSize().x;
    
    this->barrierleft->getBody()->SetTransform(b2Vec2(this->barrierleft->getSprite().getTexture()->getSize().x/(2.0f*SCALE), this->barrierleft->getSprite().getTexture()->getSize().y/(2.0f*SCALE)+ this->barrierleft->getSprite().getTexture()->getSize().x*1.0f/SCALE) ,0);
    this->barrierright->getBody()->SetTransform(b2Vec2( this->sizeX*1.0f/SCALE - this->barrierright->getSprite().getTexture()->getSize().x/(2.0f*SCALE), this->barrierright->getSprite().getTexture()->getSize().y/(2.0f*SCALE)+ this->barrierright->getSprite().getTexture()->getSize().x*1.0f/SCALE) ,0);


    this->barriertop->getBody()->SetTransform(b2Vec2(this->barriertop->getSprite().getTexture()->getSize().x/(2.0f*SCALE)+ this->barriertop->getSprite().getTexture()->getSize().y/(SCALE*1.0f), this->barriertop->getSprite().getTexture()->getSize().y/(2.0f*SCALE)),0);
    

    this->background.setPosition(sf::Vector2f(this->barrierleft->getSprite().getTexture()->getSize().x, this->barriertop->getSprite().getTexture()->getSize().y));
    this->barrierbottom = new Barrier(this->world, 0,0, "assets/horizontal.png");
    this->barrierbottom->getBody()->SetTransform(b2Vec2(this->barrierbottom->getSprite().getTexture()->getSize().x/(2.0f*SCALE) + this->barrierbottom->getSprite().getTexture()->getSize().y/(SCALE*1.0f), this->sizeY/SCALE*1.0f- this->barriertop->getSprite().getTexture()->getSize().y/(2.0f*SCALE)),0);
    
    this->finished = false;
    this->team1 = Team(1);
    this->team2 = Team(2);

    this->duck = new Duck(this->world, this->sizeX / 6, this->sizeY / 2, "assets/duck1.png");
    this->ball = new Ball(this->world, this->sizeX / 2, this->sizeY / 2, "assets/ball.png");
    this->goalside = new Goalside(this->world, this->barrierleft->getSprite().getTexture()->getSize().x , this->sizeY / 2, "assets/goalside1.png");
    this->goalside2 = new Goalside(this->world, this->sizeX - this->barrierleft->getSprite().getTexture()->getSize().x, this->sizeY / 2, "assets/goalside2.png");
    this->team1.addPlayer(1, this->duck);
}

void Game::update()
{
    sf::RenderWindow window(sf::VideoMode(this->sizeX, this->sizeY, 32), "P@oBall");
    window.setFramerateLimit(60);
    while (window.isOpen())
    {
        this->processMovement();
        window.clear(sf::Color::Black);
        window.draw(this->background);
        this->team1.draw(&window);
        this->ball->draw(&window);
        this->goalside->draw(&window);
        this->goalside2->draw(&window);
        this->barriertop->draw(&window);
        this->barrierbottom->draw(&window);
        this->barrierleft->draw(&window);
        this->barrierright->draw(&window);
        window.display();
        this->world->Step(1 / 60.f, 8, 3);
    }
}
