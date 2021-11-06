//* bad library
//* utility
// * timer - for timing things

//* headers
#include "lib/util/Timer.h"

namespace Lib1104A 
{
    namespace Utility 
    {
        Timer::Timer() 
            : m_start {pros::millis()},
              m_mark {0},
              m_last {0}
        {
            //* do nothing
        }

        Timer::~Timer() 
        {
            //* do nothing
        }

        void Timer::set() const
        {
            m_mark = pros::millis();
        }

        void Timer::clear() const 
        {
            m_mark = 0;
        }

        Misc::ms_t Timer::getTime() const 
        {
            return pros::millis() - m_start;
        }

        Misc::ms_t Timer::getDtFromLast() const 
        {
            Misc::ms_t v_returnVal = pros::millis() - m_last;
            m_last = pros::millis();
            return v_returnVal;
        }

        Misc::ms_t Timer::getDtFromMark() const 
        {
            return pros::millis() - m_mark;
        }
    }
}