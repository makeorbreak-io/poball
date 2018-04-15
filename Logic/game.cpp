#include "game.h"

Game *Game::instance = NULL;
sf::Mutex *Game::mut = new sf::Mutex();

Game::Game()
{
<<<<<<< HEAD
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
=======
    Game::instance = this;
    std::pair<int, int> *info = this->socket->registerPlayer();
    if (info == NULL) {
      std::cout << "Server did not respond\n";
      return;
    }

    this->my_id = info->second;
    this->finished = false;
    b2Vec2 Gravity(0.0f, 0.0f);
    this->world = new b2World(Gravity);
    this->players = std::unordered_map<int, Duck *>();

    this->duck = NULL;
}

void Game::update() {
    std::cout << "Starting game!\n";
    sf::RenderWindow window(sf::VideoMode(800, 600, 30), "P@oBall");
>>>>>>> b2535bb49206a9723bac1ac09288195a80c5ab4a
    window.setFramerateLimit(60);
    while (true) {
        this->processMovement();
        window.clear(sf::Color::Black);
        window.draw(this->background);
        this->team1.draw(&window);
<<<<<<< HEAD
        this->ball->draw(&window);
        this->goalside->draw(&window);
        this->goalside2->draw(&window);
        this->barriertop->draw(&window);
        this->barrierbottom->draw(&window);
        this->barrierleft->draw(&window);
        this->barrierright->draw(&window);
=======
        this->team2.draw(&window);
>>>>>>> b2535bb49206a9723bac1ac09288195a80c5ab4a
        window.display();

        this->world->Step(1 / 60.f, 8, 3);
    }
}
<<<<<<< HEAD
=======

void Game::serverListener() {
  std::istringstream msg_stream, type_stream;
  std::string msg_type;

  while (true) {
    msg_stream = Game::instance->socket->getServerMsg();
    if (!msg_stream.good()) {
      continue;
    }
    msg_stream >> msg_type;

    if (msg_type.compare("STATE") == 0) {
      Game::instance->updateState(msg_stream);
    }
    else if (msg_type.compare("NEW_PLAYER") == 0) {
      Game::instance->addPlayer(msg_stream);
    }
  }
}


void Game::updateState(std::istringstream &stream) {
 std::string line;
 stream >> line;
 int ball_x, ball_y;
 std::istringstream ball_stream = std::istringstream(line);
 ball_stream >> ball_x >> ball_y;

 if (!stream.eof()) {
   do {
     stream >> line;
     std::istringstream player_stream = std::istringstream(line);
     unsigned int player_id, x, y;
     player_stream >> player_id >> x >> y;
     Game::mut->lock();
     this->players[player_id]->move(x, y);
     Game::mut->unlock();
   } while(!stream.eof());
 }
}

void Game::addPlayer(std::istringstream &stream) {
  int player_id, player_team, x, y;
  stream >> player_id >> player_team >> x >> y;

  std::cout << "Adding player " << player_id << " X = " << x << ", Y = " << y << "\n";
  Duck *new_duck =  new Duck(this->world, x*1.0, y*1.0, "assets/duck1.png");
  this->newPlayer(player_id, new_duck);
  if (this->duck == NULL) {
    this->duck = new_duck;
  }


  if (player_team == 0) {
    this->team1.addPlayer(player_id, new_duck);
  }
  else if (player_team == 1) {
    this->team2.addPlayer(player_id, new_duck);
  }
}

void Game::newPlayer(int player_id, Duck *new_duck) {
  Game::mut->lock();
  this->players[player_id] = new_duck;
  Game::mut->unlock();
}

void Game::processMovement() {
    sf::Keyboard keyboard;
    if (this->duck == NULL) {
      std::cout << "Duc is null\n";
      return;
    }
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
>>>>>>> b2535bb49206a9723bac1ac09288195a80c5ab4a
