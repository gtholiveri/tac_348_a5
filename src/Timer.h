#ifndef TIMER_H
#define TIMER_H

#include "Particle.h"

class Timer {
   public:
    uint32_t duration;
    uint32_t startTime;
    int numRuns;
    bool* timing;

    Timer(uint32_t duration, bool* timing);
    void start();
    void act();
    void stop();
};

#endif
