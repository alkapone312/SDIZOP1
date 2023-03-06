#pragma once
#include <ctime>

namespace SDIZO {
    class Timer {
        private:
            int startTime = 0;
            int stopTime = 0;
        public:
            Timer();
            ~Timer();

            /**
             * @brief Start timer measurement.
             * 
             */
            void start();

            /**
             * @brief Stop timer measurement.
             * 
             */
            void stop();

            /**
             * @brief Get the measured time in nanoseconds
             * 
             * @return int 
             */
            int getResult();
    }   
}
