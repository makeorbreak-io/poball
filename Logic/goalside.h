#ifndef GOALSIDE_H
#define GOALSIDE_H


#include "field_object.h"
#include "team.h"
#include "game.h"

class Goalside : public Field_Object{
    private:
    	Team *team;
    	bool reset = false;
    public:
        Goalside(b2World *world, float x, float y, std::string filename, Team *team_p);
        std::string getID();
        void scoreGoal();
        bool getReset();
        bool setToggleReset();
};


#endif