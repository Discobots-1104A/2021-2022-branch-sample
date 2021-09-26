//* control - filter
//* base filter class
#include "lib/control/filter/filter.h"

namespace argonLib {
    Filter::Filter() = default;
    Filter::~Filter() = default;

    void Filter::reset() {}
    double Filter::filter(double p_UV) {return p_UV;}
}