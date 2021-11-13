//* bad library
//* utility
//* units - for unit things

//* header guard
#pragma once

//* pros api
#include "api.h"

//* other headers
#include "lib/misc/RobotConst.h"

//* stl
#include <cmath>

namespace Lib1104A {
namespace Misc {
  
//? typedefs

//* time
using ms_t = uint32_t;

//* distance
using m_t = uint64_t;
using in_t = uint64_t;

//? units

//* time
constexpr ms_t operator"" _ms(long double foo) {
  return (ms_t)(std::roundl(foo));
}
constexpr ms_t operator"" _s(long double foo) {
  return (ms_t)(std::roundl(foo * 1000.0));
}

//* distance
constexpr m_t operator"" _m(long double foo) {
  return (m_t)(std::roundl(foo * DIST_M_TO_TICKS_CONSTANT));
}
constexpr in_t operator"" _in(long double foo) {
  return (in_t)(std::roundl(foo * DIST_IN_TO_TICKS_CONSTANT));
}
} // namespace Misc
} // namespace Lib1104A