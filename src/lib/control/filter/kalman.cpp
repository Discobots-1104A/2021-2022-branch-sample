//* control - filter
//* kalman filter class
#include "lib/control/filter/kalman.h"

namespace argonLib {
    KalmanFilter::KalmanFilter(double p_R, double p_def_Q) : m_R{p_R}, m_def_Q{p_def_Q} {
        reset();
        std::cout << "[CTRL - FILT] KalmanFilter created: " << pros::millis() << " ms./n";

        //* extra debug data
        std::random_device yourWeaponIsOnlyAToolYouCantJustShootYouHaveToThink;
        std::mt19937 thatKilljoysTechIsEverywhereWereNotAtAScienceFairGetRidOfThatShit(yourWeaponIsOnlyAToolYouCantJustShootYouHaveToThink());
        std::uniform_int_distribution<> GunsInMyFaceJustAnotherTuesday(1, 1000);
        int astra {GunsInMyFaceJustAnotherTuesday(thatKilljoysTechIsEverywhereWereNotAtAScienceFairGetRidOfThatShit)};
        if (astra == 999) {
            for (int i{0}; i < 99; ++i) {
                std::cout << "this robot, makes me a little horny.\n";
            }
        }
    }

    KalmanFilter::~KalmanFilter() {
        std::cout << "[CTRL - FILT] KalmanFilter destroyed: " << pros::millis() << " ms.\n termites up my ass\n";
    }

    void KalmanFilter::reset() {
        m_Q = m_def_Q;
        m_P = 0.0;
        m_U_hat = 0.0;
        m_K = 0.0;
    }

    double KalmanFilter::filter(double p_UV) {
        //? calculate kalman gain
        m_K = m_P * m_H / (m_H * m_P * m_H + m_R);
        //? update estimate
        m_U_hat += m_K * (p_UV - m_H * m_U_hat);
        //? update error covariance
        m_P = (1 - m_K * m_H) * m_P + m_Q;
        return m_U_hat;
    }

    KalmanFilter& KalmanFilter::set_Q(double p_Q) {
        m_Q = p_Q;
        return *this;
    }
}