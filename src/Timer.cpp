#include "Timer.h"

#include "Particle.h"

Timer::Timer(uint32_t duration, bool* timing) : duration(duration), startTime(millis()), numRuns(0), timing(timing) {
  // prepended * is the dereference operator: basically what gets us
  // the *actual value* at the pointer and lets us update it
  // this should always be passed in starting as false but
  // to make it safer we'll just make it manually start at false
  *timing = false;
}

void Timer::start() {
  *timing = true;
  startTime = millis();
}

void Timer::act() {
  uint32_t currTime = millis();
  if (*timing) {
    if (currTime - startTime > duration) {
      stop();
    }
  }
}

void Timer::stop() {
  numRuns++;
  *timing = false;
}