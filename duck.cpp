#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <iostream>

#define SCALE 10

void createDuck(b2World &world, int mouse_x, int mouse_y);
void createBall(b2World &world, int mouse_x, int mouse_y);



int main() {
  sf::RenderWindow window(sf::VideoMode(800, 600, 32), "Test");
  window.setFramerateLimit(60);

  b2Vec2 Gravity(0.0f, 0.0f);
  sf::Texture duck_texture;
  duck_texture.loadFromFile("duck1.png");
  sf::Texture ball_text;
  ball_text.loadFromFile("ball.png");
  b2World world(Gravity);

  sf::Event event;
  while (window.isOpen()) {
    window.pollEvent(event);
    if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
      int mouse_x = sf::Mouse::getPosition(window).x;
      int mouse_y = sf::Mouse::getPosition(window).y;
      createDuck(world, mouse_x, mouse_y);
    }
    else if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Right) {
      int mouse_x = sf::Mouse::getPosition(window).x;
      int mouse_y = sf::Mouse::getPosition(window).y;
      createBall(world, mouse_x, mouse_y);
    }

    window.clear(sf::Color::Black);
    for (b2Body *it = world.GetBodyList();
    it != 0; it = it->GetNext()) {
      sf::Sprite sprite;
      if (it->GetPosition().x > (100/SCALE)) {
        sprite.setTexture(duck_texture);
        sprite.setOrigin(16.f, 16.f);
        sprite.setScale(0.03, 0.03);
        sprite.setPosition(SCALE * it->GetPosition().x, SCALE * it->GetPosition().y);
        sprite.setRotation(it->GetAngle() * 180/b2_pi);
      }
      else {
        sprite.setTexture(ball_text);
        sprite.setOrigin(16.f, 16.f);
        sprite.setScale(0.02, 0.02);
        sprite.setPosition(SCALE * it->GetPosition().x, SCALE * it->GetPosition().y);
        sprite.setRotation(it->GetAngle() * 180/b2_pi);
      }
      window.draw(sprite);
    }
    window.display();
    world.Step(1/60.f, 8, 3);
  }

  return 0;
}


void createDuck(b2World &world, int mouse_x, int mouse_y) {
  b2BodyDef def;
  def.position = b2Vec2(mouse_x/SCALE, mouse_y/SCALE);
  def.type = b2_dynamicBody;
  b2Body *body = world.CreateBody(&def);

  b2CircleShape shape;
  shape.m_p.Set(0,0);
  shape.m_radius = 1.15;
  // shape.SetAsBox((32.f/2)/SCALE, (32.f/2)/SCALE);
  b2FixtureDef fixture;
  fixture.density = 1.f;
  fixture.friction = 0.5f;
  fixture.shape = &shape;
  body->CreateFixture(&fixture);
}

void createBall(b2World &world, int mouse_x, int mouse_y) {
  b2BodyDef def;
  def.position = b2Vec2(mouse_x/SCALE, mouse_y/SCALE);
  def.type = b2_dynamicBody;
  b2Body *body = world.CreateBody(&def);

  b2CircleShape shape;
  shape.m_p.Set(0,0);
  shape.m_radius = 0.7;
  // shape.SetAsBox((32.f/2)/SCALE, (32.f/2)/SCALE);
  b2FixtureDef fixture;
  fixture.density = 1.f;
  fixture.friction = 0.5f;
  fixture.shape = &shape;
  body->CreateFixture(&fixture);
}
