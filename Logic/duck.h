#ifndef DUCK_H
#define DUCK_H


#include "field_object.h"

class Duck : public Field_Object{
    private:
          int goalsScored;
          int team;
    public:
        int id;
        Duck(b2World *world, float x, float y, std::string filename, int t);
        std::string getID();
        void resetGoal();
        void scoreGoal();
        int getGoalScored();
        int getId();
        int getTeam();
};

#endif