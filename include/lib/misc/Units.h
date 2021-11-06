//* bad library
//* utility
//* units - for unit things

//* header guard
#pragma once

//* pros api
#include "api.h"

//* other headers


//* stl
#include <cmath>


namespace Lib1104A {
    namespace Misc {
        //? typedefs
        using ms_t = uint32_t;

        //? units
        constexpr ms_t operator"" _ms(long double foo) {
            return (ms_t)(std::roundl(foo));
        }
        constexpr ms_t operator"" _s(long double foo) {
            return (ms_t)(std::roundl(foo * 1000.0));
        }
    }
}