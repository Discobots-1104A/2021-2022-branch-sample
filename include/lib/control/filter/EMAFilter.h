//* bad library
//* control
//* EMAFilter - exponential moving average filter

//* header guard
#pragma once

//* pros api
#include "api.h"

//* other headers
#include "lib/control/filter/AbstractFilter.h"

//* stl

namespace Lib1104A
{
    namespace Control
    {
        class EMAFilter : public AbstractFilter
        {
            public:
                //? ctor & dtor
                EMAFilter(double alpha);
                ~EMAFilter();

                //? setters

                // set alpha
                EMAFilter& setAlpha(double alpha);

                //? getters

                //? methods

                // reset filter
                void reset() override;

                // filter a value
                double filter(double value) override;

            private:
                //? members
                double m_alpha;
                double m_prevValue;

                //? private methods

        };
    }
}