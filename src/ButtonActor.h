#ifndef BUTTONACTOR_H
#define BUTTONACTOR_H

#include <functional>
#include "Particle.h"

class ButtonActor {
   private:
    bool rising;
    int pin;
    int32_t lastPoll;
    std::function<void()> callback;

   public:
    ButtonActor(boolean rising, int pin, std::function<void()> callback);
    void act();
};

#endif
