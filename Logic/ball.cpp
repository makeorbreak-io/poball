#include <iostream>
#include "ball.h"

Ball::Ball(b2World *world, float x, float y, std::string s) : Field_Object(world, x, y, s)
{
    this->touched = false;
    this->resize(0.10, 0.10);
}

std::string Ball::getID()
{
    return "ball";
}

void Ball::setTouched(bool touch, float dX, float dY){
    this->touched = touch;
    this->dirX = dX;
    this->dirY = dY;
}

void Ball::shootBall(){
    this->body->ApplyLinearImpulse(b2Vec2(100*this->dirX,100*this->dirY),this->body->GetPosition(),true);
}