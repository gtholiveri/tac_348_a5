#include "ButtonActor.h"

#include <functional>

#include "Particle.h"

ButtonActor::ButtonActor(boolean rising, int pin, std::function<void()> callback) : rising(rising), pin(pin), lastPoll(digitalRead(pin)), callback(callback) {}

void ButtonActor::act() {
  int32_t currPoll = digitalRead(pin);
  if (rising) {
    if (lastPoll == HIGH && currPoll == LOW) {
      callback();
    }
  } else {
    if (lastPoll == LOW && currPoll == HIGH) {
      callback();
    }
  }

  lastPoll = currPoll;
}