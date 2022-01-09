//* bad hardware shit
//* conveyor

//* headers
#include "hardware/Conveyor.h"

namespace Hardware {
//? ctor & dtor
Conveyor::Conveyor(MotorGroup &conveyorMotors) : m_conveyorMotors(conveyorMotors) {
    // do nothing
}

Conveyor::~Conveyor(void) {
    // do nothing
}

//? methods
void Conveyor::setVelocity(rpm_t velocity) {
    m_conveyorMotors.moveVelocity(velocity);
}

}