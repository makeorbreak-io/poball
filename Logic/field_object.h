#ifndef FIELD_OBJECT_H
#define FIELD_OBJECT_H

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

#define SCALE 10

class Field_Object{
  protected:
    b2Body *body;
    b2BodyDef bodyDef;
    sf::Sprite sprite;
    sf::Texture *t;
  public:
    Field_Object(b2World *world,float x, float y , std::string s); 
    void move(float x, float y);
    void resize(float x, float y);
    void rotate(float angle);
    void draw(sf::RenderWindow *window);
    virtual std::string getID() = 0;
    b2Body* getBody();
    sf::Sprite getSprite();
};

#endif