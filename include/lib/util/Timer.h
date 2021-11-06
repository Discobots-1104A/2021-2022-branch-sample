//* bad library
//* utility
//* timer - for timing things

//* header guard
#pragma once

//* pros api
#include "api.h"

//* other headers
#include "lib/misc/Units.h"

//* stl


namespace Lib1104A {
    namespace Utility {
        class Timer {
            public:
                //? constructors

                Timer();

                //? setter functions

                // set timer mark
                void set() const;
                // clear timer mark
                void clear() const;

                //? getter functions

                // get current time
                Misc::ms getTime() const;
                // get Dt from last called
                Misc::ms getDtFromLast() const;
                // get Dt from mark
                Misc::ms getDtFromMark() const;

            private:
                // timer start
                const Misc::ms m_start;
                // timer mark
                mutable Misc::ms m_mark;
                // last called
                mutable Misc::ms m_last;

        };
    }
}