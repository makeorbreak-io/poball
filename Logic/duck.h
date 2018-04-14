#include "field_object.h"

class Duck : public Field_Object{
    public:
        Duck(b2World &world, float x, float y, std::string filename);
};