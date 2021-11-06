//* bad library
//* utility
// * timer - for timing things

//* headers
#include "lib/util/Timer.h"

namespace Lib1104A {
    namespace Utility {
        Timer::Timer() 
            : m_start {pros::millis()},
              m_mark {0},
              m_last {0}
        {
            //* do nothing
        }

        void Timer::set() const{
            m_mark = pros::millis();
        }

        void Timer::clear() const {
            m_mark = 0;
        }

        Misc::ms Timer::getTime() const {
            return pros::millis() - m_start;
        }

        Misc::ms Timer::getDtFromLast() const {
            Misc::ms v_returnVal = pros::millis() - m_last;
            m_last = pros::millis();
            return v_returnVal;
        }

        Misc::ms Timer::getDtFromMark() const {
            return pros::millis() - m_mark;
        }
    }
}