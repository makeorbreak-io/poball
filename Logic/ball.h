#ifndef BALL_H
#define BALL_H


#include "field_object.h"

class Ball : public Field_Object{
    private:
        float dirX,dirY;
        bool touched;
    public:
        Ball(b2World *world, float x, float y, std::string filename);
        std::string getID();
        void setTouched(bool touch, float dX, float dY);
        void shootBall();
};


#endif