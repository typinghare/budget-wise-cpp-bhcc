#include "TimerUtil.h"

#include <QCoreApplication>

QTimer* TimerUtil::setTimeout(int delayMs, TimeoutCallback callback) {
    QTimer* timer = new QTimer(QCoreApplication::instance());
    QObject::connect(timer, &QTimer::timeout, [timer, callback]() {
        callback();
        timer->deleteLater();
    });

    timer->setSingleShot(true);
    timer->start(delayMs);

    return timer;
}

QTimer* TimerUtil::setInterval(int delayMs, IntervalCallback callback) {
    QTimer* timer = new QTimer;
    QObject::connect(timer, &QTimer::timeout, [timer, callback]() {
        if (callback()) {
            timer->stop();
            timer->deleteLater();
            QObject::connect(timer, &QTimer::destroyed, timer, &QTimer::deleteLater);
        }
    });

    timer->start(delayMs);

    return timer;
}
