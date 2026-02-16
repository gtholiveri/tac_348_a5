#include <functional>

#include "IntervalActor.cpp"
#include "Particle.h"
#include "LEDBlinker.cpp"

class LEDTimer {
    uint32_t timerDuration;
    uint32_t statusBlinkInterval;
    int blinkPin;
    bool currentlyTiming;

    LEDBlinker blinker;

    LEDTimer(uint32_t timerDuration, uint32_t statusBlinkInterval, int blinkPin,
             bool currentlyTiming)
        : timerDuration(timerDuration),
          statusBlinkInterval(statusBlinkInterval),
          blinkPin(blinkPin),
          currentlyTiming(currentlyTiming), blinker(50, 950) {}

    void start() {
        blinker.start();
    }
};