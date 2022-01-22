//* bad hardware shit
//* conveyor

//? HOLY FUCK THIS IS SO MUCH MORE SIMPLE THAN THE OTHERS

//* header guard
#pragma once

//* pros api
#include "api.h"

//* other headers
#include "lib/libApi.h"
#include "okapi/api.hpp"

//* stl
#include <cmath>

//* other shid
using okapi::MotorGroup;
using Lib1104A::Misc::rt_t;
using Lib1104A::Misc::rpm_t;

namespace Hardware {

class Conveyor {
public:
    //? ctor & dtor
    explicit Conveyor(MotorGroup &conveyorMotors);
    virtual ~Conveyor(void);

    //? setters


    //? getters


    //? methods
    void setVelocity(rpm_t velocity);

private:
    //? members
    MotorGroup &m_conveyorMotors;

    //? private methods


};
} // namespace Hardware