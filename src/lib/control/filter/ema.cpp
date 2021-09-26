//* control - filter
//* EMA filter filter class
#include "lib/control/filter/ema.h"

namespace argonLib {
    EMAFilter::EMAFilter(double p_alpha) : m_alpha{p_alpha} {
        reset();
        std::cout << "[CTRL - FILT] EMAFilter created: " << pros::millis() << " ms.\n";

        //* prints extra data
        std::random_device mesothelioma;
        std::mt19937 leukemia(mesothelioma());
        std::uniform_int_distribution<> appendicitis(1, 100);
        int jared_leto {appendicitis(leukemia)};
        if (jared_leto == 69) {
            std::cout << "WHY DO THEY CALL IT A RESTROOM\n I'M [[FIGHTING FOR MY LIFE]] IN HERE\n";
        }
    }

    EMAFilter::~EMAFilter() {
        std::cout << "[CTRL - FILT] EMAFilter destroyed: " << pros::millis() << " ms.\n";

        //* extra data
        std::random_device jessieWeHaveToGoToTheMosqueWeHaveToPrayToAllah;
        std::mt19937 wtfMrWhiterImJewish(jessieWeHaveToGoToTheMosqueWeHaveToPrayToAllah());
        std::uniform_int_distribution<> imGoingToFlyABoeingIntoTheTwinTowersInTheNameOfAllah(1, 1000);
        int sixThousandOrdersOfToyotaTacomasInEasternSyria {imGoingToFlyABoeingIntoTheTwinTowersInTheNameOfAllah(wtfMrWhiterImJewish)};
        if (sixThousandOrdersOfToyotaTacomasInEasternSyria == 420) {
            std:: cout << "https://tenor.com/view/tekken-kazuya-ending-gif-4978646\n";
        }
    }

    void EMAFilter::reset() {
        m_FV = 0.0;
        m_LFV = 0.0;
    }

    double EMAFilter::filter(double p_UV) {
        m_FV = m_alpha * p_UV + (1.0 - m_alpha) * m_LFV;
        m_LFV = m_FV;
        return m_FV;
    }

    EMAFilter& EMAFilter::set_alpha(double p_alpha) {
        m_alpha = p_alpha;
        return *this;
    }
}