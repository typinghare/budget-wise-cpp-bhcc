#include "Timer.h"

#include <QTimer>

void Timer::setTimeout(int delayMs, TimeoutCallback callback) {
//    QTimer::singleShot(delayMs, std::move(callback));
}

void Timer::setInterval(int delayMs, IntervalCallback callback) {
    QTimer* timer = new QTimer;
    QObject::connect(timer, &QTimer::timeout, [timer, callback]() {
        if (callback()) {
            timer->stop();
            timer->deleteLater();
            QObject::connect(timer, &QTimer::destroyed, timer, &QTimer::deleteLater);
        }
    });

    timer->start(delayMs);
}
