#include "game.h"
#include <chrono>
#include <thread>



Game::Game(){
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

    this->duck = new Duck(this->world, this->sizeX / 6, this->sizeY / 2, "assets/duck1.png",1);
    this->duck2 = new Duck(this->world, this->sizeX / 6, this->sizeY / 2, "assets/duck2.png",1);
    this->ball = new Ball(this->world, this->sizeX / 2, this->sizeY / 2, "assets/ball.png");
    this->goalside = new Goalside(this->world, this->barrierleft->getSprite().getTexture()->getSize().x , this->sizeY / 2, "assets/goalside1.png", this->duck2);
    this->goalside2 = new Goalside(this->world, this->sizeX - this->barrierleft->getSprite().getTexture()->getSize().x, this->sizeY / 2, "assets/goalside2.png", this->duck);

    this->window =  new sf::RenderWindow(sf::VideoMode(this->sizeX, this->sizeY, 32), "P@oBall");

    this->window->setFramerateLimit(60);



sf::Font MyFont;
if (!MyFont.loadFromFile("DroidSerif.ttf")){
    std::cout << "FONT NOT LOADED";
}


sf::Text text;

// select the font
text.setFont(MyFont); // font is a sf::Font

// set the string to display
text.setString("Score");

text.setPosition(0.4f, 0.4f);

// set the character size
text.setCharacterSize(24); // in pixels, not points!

// set the text style
text.setStyle(sf::Text::Bold | sf::Text::Underlined);

this->font = MyFont;
this->score = text;



}

void Game::update(){
    while (this->window->isOpen()){
        this->processMovement();
        this->window->clear(sf::Color::Black);
        this->window->draw(this->background);
        this->handleReset();
        this->duck->draw(this->window);
        this->ball->draw(this->window);
        this->goalside->draw(this->window);
        this->goalside2->draw(this->window);
        this->barriertop->draw(this->window);
        this->barrierbottom->draw(this->window);
        this->barrierleft->draw(this->window);
        this->barrierright->draw(this->window);
        //this->window->draw(this->score);
        if(this->checkWinning() != nullptr){
            this->won(this->checkWinning()->getTeam());
            return;
        }
        this->window->display();
        this->world->Step(1 / 60.f, 8, 3);

    }
}

void Game::processMovement() {
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


Duck * Game::checkWinning(){
    if(this->duck->getGoalScored() > 3){
        return this->duck;
    }
    if(this->duck2->getGoalScored() > 3){
        return this->duck2;
    }
    return nullptr;
}

void Game::resetGoal(){
    std::cout << "Reseting game\n";
} 

void Game::handleReset(){
    if(this->goalside->getReset() || this->goalside2->getReset()){
        this->duck->resetPos();
        this->ball->resetPos();
        this->goalside->setToggleReset();this->goalside2->setToggleReset();
    }
}
void Game::won(int id){
    std::cout << "Team " << id << " WON. \n";
    auto winscreen = new Barrier(this->world, 390,310, "assets/win.jpg");
    winscreen->draw(this->window);
    this->window->display();
    std::this_thread::sleep_for(std::chrono::milliseconds(5000));
}

Ball* Game::getBall(){
    return this->ball;
}


Duck * Game:: getDuck(){
    return this->duck;
}

