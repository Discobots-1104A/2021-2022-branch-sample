//* bad library
//* control
//* Passthrough - a filter that passes all data through

//* headers
#include "lib/control/filter/PassthroughFilter.h"

namespace Lib1104A
{
    namespace Control
    {
        PassthroughFilter::PassthroughFilter()
        {
            // do nothing
        }

        PassthroughFilter::~PassthroughFilter()
        {
            // do nothing
        }

        void PassthroughFilter::reset()
        {
            // do nothing
        }

        double PassthroughFilter::filter(double value)
        {
            return value;
        }
    }
}