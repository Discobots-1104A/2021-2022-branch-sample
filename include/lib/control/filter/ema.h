//* control - filter
//* EMA filter class
#pragma once
#include "lib/control/filter/filter.h"
#include <random>

namespace argonLib {
    class EMAFilter : public Filter {
        public:
            explicit EMAFilter(double p_alpha);
            virtual ~EMAFilter();

            void reset(void) override;
            double filter(double p_UV) override;
            EMAFilter& set_alpha (double p_alpha);

        private:
            double m_alpha;
            double m_FV;
            double m_LFV;

    };
}
