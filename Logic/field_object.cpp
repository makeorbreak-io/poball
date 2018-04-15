#include <iostream>
#include <math.h>
#include "field_object.h"

Field_Object::Field_Object(b2World *world, float x, float y, std::string s)
{
  this->t = new sf::Texture();
  this->t->loadFromFile(s);
  this->sprite.setTexture(*this->t);
  this->sprite.setOrigin(this->t->getSize().x/2.0f, this->t->getSize().y/2.0f);
  this->sprite.setPosition(x+this->sprite.getOrigin().x, y+this->sprite.getOrigin().y);
  this->sprite.rotate(90);
  this->bodyDef.position = b2Vec2(x / SCALE, y / SCALE);
}

void Field_Object::move(float x, float y)
{
  this->body->ApplyLinearImpulse(b2Vec2(x, y), this->body->GetPosition(), true);
}

void Field_Object::resize(float x, float y)
{
  this->sprite.scale(x, y);
}

void Field_Object::draw(sf::RenderWindow *window)
{
  this->sprite.setPosition(this->body->GetPosition().x * SCALE, this->body->GetPosition().y * SCALE);
  this->sprite.setRotation(this->body->GetAngle()*180.0f/M_PI);
  window->draw(this->sprite);
}

b2Body *Field_Object::getBody()
{
  return this->body;
}

sf::Sprite Field_Object::getSprite(){
  return this->sprite;
}
