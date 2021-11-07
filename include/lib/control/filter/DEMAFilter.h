//* bad library
//* control
//* DEMAFilter - double exponential moving average filter
//* kinda just for experimenting stuff

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
        class DEMAFilter : public AbstractFilter
        {
            public:
                //? ctor & dtor
                DEMAFilter(double alpha);
                ~DEMAFilter();

                //? setters

                // set alpha
                DEMAFilter& setAlpha(double alpha);

                //? getters

                //? methods

                // reset filter
                void reset() override;

                // filter
                double filter(double value) override;

            private:
                //? members
                double m_alpha;
                double m_prevValue;
                double m_prevValue2;

                //? private methods
                double ema(double value, double prev);
        };
    }
}