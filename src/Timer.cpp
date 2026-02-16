#include "Particle.h"

class Timer {
   public:
    uint32_t duration;
    uint32_t startTime;
    int numRuns;
    bool* timing;

    Timer(uint32_t duration, bool* timing)
        : duration(duration), startTime(millis()), numRuns(0), timing(timing) {
        // prepended * is the dereference operator: basically what gets us
        // the *actual value* at the pointer and lets us update it
        // this should always be passed in starting as false but
        // to make it safer we'll just make it manually start at false
        *timing = false;
    }

    void start() {
        *timing = true;
        startTime = millis();
    }


    void act() {
        uint32_t currTime = millis();
        if (timing) {
            if (currTime - startTime > duration) {
                stop();
            }
        }
    }



    void stop() {
        numRuns++;
        *timing = false;
    }
};