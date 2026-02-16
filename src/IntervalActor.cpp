#include <functional>
#include "Particle.h"

class IntervalActor {
   public:
    uint32_t interval;
    uint32_t offset;
    uint32_t lastRun;
    std::function<void()> callback;

    IntervalActor(uint32_t interval, uint32_t offset, std::function<void()> callback) :
        interval(interval), offset(offset), lastRun(millis() - offset), callback(callback) {}

    void act() {
        uint32_t currTime = millis();

        if (currTime - lastRun >= interval) {
            lastRun = currTime;
            callback();
        } else {
            // do nothing
        }
    }

    void reset(uint32_t syncedTime) {
        lastRun = syncedTime - offset;
    }

    void reset() {
        lastRun = millis() - offset;
    }
};