#include "LEDTimer.h"

LEDTimer::LEDTimer(uint32_t duration, bool* timing, std::function<void()> onFinish) : duration(duration), startTime(millis()), numRuns(0), timing(timing), onFinish(onFinish) {
    // prepended * is the dereference operator: basically what gets us
    // the *actual value* at the pointer and lets us update it
    // this should always be passed in starting as false but
    // to make it safer we'll just make it manually start at false
    *timing = false;
}

void LEDTimer::start() {
    *timing = true;
    startTime = millis();
}

void LEDTimer::act() {
    uint32_t currTime = millis();
    if (*timing) {
        if (currTime - startTime > duration) {
            finish();
        }
    }
}

void LEDTimer::finish() {
    numRuns++;
    *timing = false;
    onFinish(); // run the onFinish callback (in this project, runs the end flash seq)
}

void LEDTimer::stop() {
    // note: we don't count this towards numRuns
    *timing = false;
}