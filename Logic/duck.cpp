#include "duck.h"

Duck::Duck(b2World &world, float x, float y, std::string s) : Field_Object(world, x, y)
{
    sf::Texture t = sf::Texture();
    t.loadFromFile(s);
    this->sprite.setTexture(t);
}