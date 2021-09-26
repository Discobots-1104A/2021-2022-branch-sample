//* control - filter
//* base filter class

#pragma once
#include "api.h"

namespace argonLib {
    class Filter {
        public:
            Filter();
            virtual ~Filter();

            virtual void reset(void);
            virtual double filter(double p_UV);
    };
}
