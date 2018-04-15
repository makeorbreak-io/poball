#include <iostream>
#include <string>
#include "duck.h"

Duck::Duck(b2World *world, float x, float y, std::string s,int t) : Field_Object(world, x, y, s)
{
    this->team = t;
    this->goalsScored = 0;
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

void Duck::scoreGoal(){
	std::cout << "GOAL Team :" << this->id << " scored a GOAL. \n";
	this->goalsScored += 1;
}

void Duck::resetGoal(){
	this->goalsScored = 0;
}

int Duck::getGoalScored(){
	return this->goalsScored;
}

int Duck::getTeam(){
    return this->team;
}