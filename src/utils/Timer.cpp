#include "utils/Timer.h"

using namespace SDIZO;

Timer::Timer() {}

Timer::~Timer() {}

void Timer::start() {
    this->startTime = clock();
}

void Timer::stop() {
    this->stopTime = clock();
}

int Timer::getResult() {
    return this->stopTime - this->startTime;
}