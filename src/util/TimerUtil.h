#ifndef TIMERUTIL_H
#define TIMERUTIL_H

#include <functional>
#include <QTimer>

using TimeoutCallback = std::function<void()>;

using IntervalCallback = std::function<bool()>;

class TimerUtil {
public:
    /**
     * @brief Schedules an timeout.
     * @param delayMs - The delay in milliseconds before calling the callback.
     * @param callback - The function to be called after the specified delay.
     */
    static QTimer* setTimeout(int delayMs, TimeoutCallback callback);

    /**
     * @brief Schedules an delay.
     * @param delayMs - The interval in milliseconds between each execution of the callback.
     * @param callback - The function to be called at regular intervals; If the callback
     * returns true, the interval stops.
     */
    static QTimer* setInterval(int delayMs, IntervalCallback callback);
};

#endif // TIMERUTIL_H
