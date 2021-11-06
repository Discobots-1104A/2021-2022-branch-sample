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
        using ms = uint32_t;

        //? units
        constexpr ms operator"" _ms(long double foo) {
            return (ms)(std::roundl(foo));
        }
        constexpr ms operator"" _s(long double foo) {
            return (ms)(std::roundl(foo * 1000.0));
        }
    }
}