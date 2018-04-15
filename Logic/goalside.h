#ifndef GOALSIDE_H
#define GOALSIDE_H


#include "field_object.h"
#include "game.h"
#include "duck.h"

class Goalside : public Field_Object{
    private:
    	bool reset = false;
        Duck * duck;
    public:
        Goalside(b2World *world, float x, float y, std::string filename, Duck * duck);
        std::string getID();
        void scoreGoal();
        bool getReset();
        bool setToggleReset();
};


#endif