#ifndef TIMER_H
#define TIMER_H

#include <functional>

using TimeoutCallback = std::function<void()>;

using IntervalCallback = std::function<bool()>;

class Timer {
public:
    /**
     * @brief Schedules an timeout.
     * @param delayMs - The delay in milliseconds before calling the callback.
     * @param callback - The function to be called after the specified delay.
     */
    static void setTimeout(int delayMs, TimeoutCallback callback);

    /**
     * @brief Schedules an delay.
     * @param delayMs - The interval in milliseconds between each execution of the callback.
     * @param callback - The function to be called at regular intervals; If the callback
     * returns true, the interval stops.
     */
    static void setInterval(int delayMs, IntervalCallback callback);
};

#endif // TIMER_H
