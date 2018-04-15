#include <iostream>
#include <math.h>
#include "field_object.h"

Field_Object::Field_Object(b2World *world, float x, float y, std::string s)
{
  this->t = new sf::Texture();
  this->t->loadFromFile(s);
  this->sprite.setTexture(*this->t);
  this->sprite.setPosition(x, y);
  this->sprite.rotate(90);
  this->bodyDef.position = b2Vec2(x / SCALE, y / SCALE);
  this->bodyDef.type = b2_dynamicBody;
  this->bodyDef.linearDamping = 5.0f;
  //this->bodyDef.angularDamping = 5.0f;
  b2FixtureDef fixture;
  b2CircleShape shape;
  shape.m_p.Set(0, 0);
  shape.m_radius = this->t->getSize().x / (SCALE * 20);
  fixture.density = .08;
  fixture.friction = .2f;
  fixture.shape = &shape;
  this->body = world->CreateBody(&this->bodyDef);
  this->body->CreateFixture(&fixture);
}

void Field_Object::move(float x, float y)
{
  this->body->ApplyLinearImpulse(b2Vec2(x,y),this->body->GetPosition(),true);
}

void Field_Object::resize(float x, float y)
{
  this->sprite.scale(x, y);
}

void Field_Object::draw(sf::RenderWindow *window)
{
  this->sprite.setPosition(this->body->GetPosition().x*SCALE, this->body->GetPosition().y*SCALE);
  window->draw(this->sprite);
}
