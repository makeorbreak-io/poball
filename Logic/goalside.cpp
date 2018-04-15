#include "goalside.h"

Goalside::Goalside(b2World *world, float x, float y, std::string s) : Field_Object(world, x, y, s)
{
    b2FixtureDef fixture;
    b2PolygonShape shape;
    shape.SetAsBox(this->sprite.getOrigin().x  * 0.2/ SCALE, this->sprite.getOrigin().y  * 0.2 / SCALE);
    fixture.density = .08;
    fixture.friction = .2f;
    fixture.shape = &shape;
    this->bodyDef.type = b2_staticBody;
    //this->bodyDef.fixedRotation = true;
    this->body = world->CreateBody(&this->bodyDef);
    this->body->CreateFixture(&fixture);
    this->body->SetUserData(this);
    this->sprite.scale(0.2f,0.2f);
}

std::string Goalside::getID()
{
    return "goalside";
}