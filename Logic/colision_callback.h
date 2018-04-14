#ifndef COLISION_CALLBACK_H
#define COLISION_CALLBACK_H

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <iostream>
#include "ball.h"
#include "duck.h"
#include <string.h>

class MyContactListener : public b2ContactListener
{
    void BeginContact(b2Contact *contact)
    {
        void *bodyUserDataA = contact->GetFixtureA()->GetBody()->GetUserData();
        void *bodyUserDataB = contact->GetFixtureB()->GetBody()->GetUserData();

        Field_Object *bA = static_cast<Field_Object *>(bodyUserDataA);
        Field_Object *bB = static_cast<Field_Object *>(bodyUserDataB);


        float xA =  bA->getBody()->GetPosition().x;
        float yA = bA->getBody()->GetPosition().y;

        float xB = bB->getBody()->GetPosition().x;
        float yB = bB->getBody()->GetPosition().y;

        if (bA->getID().compare("ball") == 0 && bB->getID().compare("duck") == 0)
        {
            Ball *ball = static_cast<Ball *>(bA);
            ball->setTouched(true, xA - xB, yA-yB);
        }
        else if (bA->getID().compare("duck") == 0 && bB->getID().compare("ball") == 0)
        {
            Ball *ball = static_cast<Ball *>(bB);
            ball->setTouched(true, xB - xA, yB - yA);
        }
    }
    void EndContact(b2Contact *contact)
    {

        void *bodyUserDataA = contact->GetFixtureA()->GetBody()->GetUserData();
        void *bodyUserDataB = contact->GetFixtureB()->GetBody()->GetUserData();

        Field_Object *bA = static_cast<Field_Object *>(bodyUserDataA);
        Field_Object *bB = static_cast<Field_Object *>(bodyUserDataB);


        if (bA->getID().compare("ball") == 0 && bB->getID().compare("duck") == 0)
        {
            Ball *ball = static_cast<Ball *>(bA);
            ball->setTouched(false, 0, 0);
        }
        else if (bA->getID().compare("duck") == 0 && bB->getID().compare("ball") == 0)
        {
            Ball *ball = static_cast<Ball *>(bB);
            ball->setTouched(false, 0, 0);
        }
    }
};

#endif