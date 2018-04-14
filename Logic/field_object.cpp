#include "field_object.h"

Field_Object::Field_Object(b2World *world, float x, float y, std::string s)
{
  this->t = new sf::Texture();
  this->t->loadFromFile(s);
  this->sprite.setTexture(*this->t);
  this->sprite.setPosition(x, y);
  this->bodyDef.position = b2Vec2(x / SCALE, y / SCALE);
  this->bodyDef.type = b2_dynamicBody;
  this->body = world->CreateBody(&this->bodyDef);
}

void Field_Object::move(float x, float y)
{
  this->sprite.move(x, y);
  this->body->SetTransform(b2Vec2(x/SCALE, y/SCALE), 0);
}

void Field_Object::resize(float x, float y)
{
  this->sprite.scale(x, y);
  b2CircleShape shape;
  shape.m_p.Set(0, 0);
  shape.m_radius = this->sprite.getPosition().x / SCALE;
  b2FixtureDef fixture;
  //fixture.density = 1.f;
  //fixture.friction = 0.5f;
  fixture.shape = &shape;
  this->body->CreateFixture(&fixture);
}

void Field_Object::draw(sf::RenderWindow *window)
{
  window->draw(this->sprite);
}

void Field_Object::rotate(float angle){
  this->sprite.setRotation(angle);
}
