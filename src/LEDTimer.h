#ifndef LEDTIMER_H
#define LEDTIMER_H

#include <functional>
#include "Particle.h"

class LEDTimer {
   public:
    uint32_t duration;
    uint32_t startTime;
    int numRuns;
    bool* timing;
    std::function<void()> onEnd;

    LEDTimer(uint32_t duration, bool* timing, std::function<void()> onEnd);
    void start();
    void act();
    void stop();
};

#endif