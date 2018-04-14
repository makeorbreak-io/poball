#include <iostream>
#include "duck.h"

Duck::Duck(b2World *world, float x, float y, std::string s) : Field_Object(world, x, y,s)
{this->resize(0.10,0.10);}