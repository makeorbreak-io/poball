#ifndef DUCK_H
#define DUCK_H


#include "field_object.h"

class Duck : public Field_Object{
    private:
        int id;
    public:
        Duck(b2World *world, float x, float y, std::string filename);
        std::string getID();
};

#endif