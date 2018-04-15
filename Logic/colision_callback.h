#ifndef COLISION_CALLBACK_H
#define COLISION_CALLBACK_H

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <iostream>
#include "ball.h"
#include "goalside.h"
#include "duck.h"
#include <string.h>


class MyContactListener : public b2ContactListener {
    void BeginContact(b2Contact *contact);
    void EndContact(b2Contact *contact);
};

#endif