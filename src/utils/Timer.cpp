#include "utils/Timer.h"

using namespace SDIZO;

void Timer::start() {
    this->startTime = clock();
}

void Timer::stop() {
    this->stopTime = clock();
}

int Timer::getResult() {
    return this->stopTime - this->startTime;
}