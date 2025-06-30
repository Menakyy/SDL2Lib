#ifndef UTILS_TIMER
#define UTILS_TIMER
#include <chrono>

class Timer
{
public:
    Timer() : running(false), durationMs(0) {}

    void start(int ms)
    {
        durationMs = ms;
        startTime  = std::chrono::steady_clock::now();
        running    = true;
    }

    bool isGoingOn() const { return running && !isElapsed(); }

    bool isElapsed() const
    {
        if (!running)
        {
            return false;
        }
        auto now = std::chrono::steady_clock::now();
        return std::chrono::duration_cast<std::chrono::milliseconds>(now - startTime).count() >= durationMs;
    }

    bool isTurnedOff() const { return !running; }

    void stop() { running = false; }

private:
    std::chrono::steady_clock::time_point startTime;
    int                                   durationMs;
    bool                                  running;
};


#endif /* UTILS_TIMER */
