#ifndef GOALSIDE_H
#define GOALSIDE_H


#include "field_object.h"

class Goalside : public Field_Object{
    private:
    public:
        Goalside(b2World *world, float x, float y, std::string filename);
        std::string getID();
};


#endif