#include "IntervalActor.h"

#include <functional>
#include "Particle.h"

    IntervalActor::IntervalActor(uint32_t interval, uint32_t offset, std::function<void()> callback) :
        interval(interval), offset(offset), lastRun(millis() - offset), callback(callback) {}

    void IntervalActor::act() {
        uint32_t currTime = millis();

        if (currTime - lastRun >= interval) {
            lastRun = currTime;
            callback();
        } else {
            // do nothing
        }
    }

    void IntervalActor::reset(uint32_t syncedTime) {
        lastRun = syncedTime - offset;
    }

    void IntervalActor::reset() {
        lastRun = millis() - offset;
    }