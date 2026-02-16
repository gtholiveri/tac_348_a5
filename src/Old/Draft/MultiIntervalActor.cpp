#include <functional>

#include "Particle.h"

class MultiIntervalActor {
   public:
    /*the asterisks here mean that we define these variables as pointers /
    references which is bizarre to me coming from java where everything is a
    reference by default but we need this to be able to overwrite these to a
    dynamic size using new otherwise we actually have a type mismatch (again,
    C++ is so bizarre coming from garbage collected Java) from trying to store a
    pointer to the actual value
    In yet another weird and terrible C++ change, when you make a pointer and
    want it to point to an array, it doesn't actually know how long it is
    So you could end up corrupting memory and literally overwriting random unknown
    memory addresses if you don't very carefully keep track of it yourself.
    */
    uint32_t* intervals;
    uint32_t* lastRuns;
    std::function<void()>* callbacks;
    int numActions;

    MultiIntervalActor(
        // initializer_list is basically syntactic sugar for declaring
        // a varargs of lists, in this case varargs of pairs
        std::initializer_list<std::pair<uint32_t, std::function<void()>>>
            interFuncPairs) {
        numActions = interFuncPairs.size();
        intervals = new uint32_t[numActions];
        lastRuns = new uint32_t[numActions];
        callbacks = new std::function<void()>[numActions];

        uint32_t unifiedStartTime = millis();
        int i = 0;
        // "auto" infers type since the type declaration is long
        // const necessary because std::initializer_list is strictly
        // unmodifiable so when we declare the type here have to put const
        // and apparently the "&" means that we retrieve strictly references
        // instead of copying values
        for (const auto& interFuncPair : interFuncPairs) {
            lastRuns[i] = unifiedStartTime;
            intervals[i] = interFuncPair.first;
            callbacks[i] = interFuncPair.second;
            i++;
        }
    }

    void act() {
        uint32_t currTime = millis();

        for (int i = 0; i < numActions; i++)
            if (currTime - lastRuns[i] >= intervals[i]) {
                lastRuns[i] = currTime;
                callbacks[i]();
            } else {
                // do nothing
            }
    }
};