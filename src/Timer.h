#ifndef TIMER_H
#define TIMER_H

#include <functional>
#include "Particle.h"

class Timer {
   public:
    uint32_t duration;
    uint32_t startTime;
    int numRuns;
    bool* timing;
    std::function<void()> onEnd;

    Timer(uint32_t duration, bool* timing, std::function<void()> onEnd);
    void start();
    void act();
    void stop();
};

#endif