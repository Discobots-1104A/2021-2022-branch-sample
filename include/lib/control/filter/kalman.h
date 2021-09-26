//* control - filter
//* kalman filter class
#pragma once
#include "lib/control/filter/filter.h"
#include <random>

namespace argonLib {
    class KalmanFilter : public Filter {
        public:
            explicit KalmanFilter(double p_R, double p_def_Q);
            virtual ~KalmanFilter();

            void reset(void) override;
            double filter(double p_UV) override;
            KalmanFilter& set_Q(double p_Q);

        private:
            const double m_R; // noise covariance
            const double m_H {1.0}; // measure map scalar
            const double m_def_Q; // default covariance estimate
            double m_Q; // covariance estimate
            double m_P {0.0}; // error covariance estimate
            double m_U_hat {0.0}; // estimated state
            double m_K {0.0}; // Kalman gain
        
    };
}