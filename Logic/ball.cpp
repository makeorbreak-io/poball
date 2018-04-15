#include <iostream>
#include "ball.h"

Ball::Ball(b2World *world, float x, float y, std::string s) : Field_Object(world, x, y, s)
{
    b2FixtureDef fixture;
    b2CircleShape shape;
    shape.m_p.Set(0, 0);
    shape.m_radius = this->sprite.getOrigin().x * 0.05 / SCALE;
    fixture.density = .08;
    fixture.friction = .2f;
    fixture.restitution = 0.7f;
    fixture.shape = &shape;
    this->bodyDef.type = b2_dynamicBody;
    this->bodyDef.linearDamping = 5.0f;
    this->bodyDef.angularDamping = .4f;
    this->bodyDef.fixedRotation = false;
    this->body = world->CreateBody(&this->bodyDef);
    this->body->CreateFixture(&fixture);
    this->body->SetUserData(this);
    this->touched = false;
    this->resize(0.05, 0.05);
}

std::string Ball::getID()
{
    return "ball";
}

void Ball::setTouched(bool touch, float dX, float dY)
{
    this->touched = touch;
    this->dirX = dX;
    this->dirY = dY;
}

void Ball::shootBall()
{
    this->body->ApplyLinearImpulse(b2Vec2(100 * this->dirX, 100 * this->dirY), this->body->GetPosition(), true);
}