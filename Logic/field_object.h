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
    Field_Object(){};
    Field_Object(b2World *world,float x, float y , std::string s); 
    void move(float x, float y);
    void resize(float x, float y);
    void draw(sf::RenderWindow *window);
};