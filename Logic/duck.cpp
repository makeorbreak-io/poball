#include <iostream>
#include <string>
#include "duck.h"

Duck::Duck(b2World *world, float x, float y, std::string s) : Field_Object(world, x, y, s)
{
    b2FixtureDef fixture;
    b2CircleShape shape;
    shape.m_p.Set(0, 0);
    shape.m_radius = this->sprite.getOrigin().x * 0.1 / (SCALE);
    fixture.density = .08;
    fixture.friction = .2f;
    fixture.shape = &shape;
    this->bodyDef.type = b2_dynamicBody;
    this->bodyDef.linearDamping = 5.0f;
    this->bodyDef.angularDamping = .4f;
    this->body = world->CreateBody(&this->bodyDef);
    this->body->CreateFixture(&fixture);
    this->body->SetUserData(this);
    this->resize(0.10, 0.10);
}

std::string Duck::getID()
{
    return "duck";
}