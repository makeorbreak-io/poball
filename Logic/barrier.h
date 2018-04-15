#ifndef BARRIER_H
#define BARRIER_H

#include "field_object.h"

class Barrier : public Field_Object{
    private:
    public:
        Barrier(b2World *world, float x, float y, std::string filename);
        std::string getID();
};

#endif
