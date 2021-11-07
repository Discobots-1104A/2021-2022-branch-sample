//* bad library
//* control
//* EMAFilter - exponential moving average filter

//* headers
#include "lib/control/filter/EMAFilter.h"

namespace Lib1104A
{
    namespace Control
    {
        EMAFilter::EMAFilter(double alpha)
            : m_alpha {alpha},
              m_prevValue{0.0}
        {
            // do nothing
        }

        EMAFilter::~EMAFilter()
        {
            // do nothing
        }

        EMAFilter& EMAFilter::setAlpha(double alpha)
        {
            m_alpha = alpha;
            return *this;
        }

        void EMAFilter::reset()
        {
            m_prevValue = 0.0;
        }

        double EMAFilter::filter(double value)
        {
            // based on what i read from Pieter P
            double result = m_alpha * value + (1.0 - m_alpha) * m_prevValue;
            m_prevValue = result;
            return result;
        }
    }
}