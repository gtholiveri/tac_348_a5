#include "LEDTimer.h"

LEDTimer::LEDTimer(uint32_t duration, bool* timing, std::function<void()> onEnd) : duration(duration), startTime(millis()), numRuns(0), timing(timing), onEnd(onEnd) {
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
      stop();
    }
  }
}

void LEDTimer::stop() {
  numRuns++;
  *timing = false;
  onEnd();
}