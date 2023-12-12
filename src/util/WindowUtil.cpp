#include "TimerUtil.h"

#include <QtMath>
#include <QDebug>
#include <QMessageBox>

#include "WindowUtil.h"

void WindowUtil::jump(QWidget *from, QWidget *to, bool smooth) {
    if (to == nullptr) {
        // Unable to navigate to another window
        return;
    }

    if (smooth) {
        int fromHeight = from->height();
        int fromWidth = from->width();
        int toHeight = to->height();
        int toWidth = to->width();

        to->resize(fromWidth, fromHeight);
        to->show();

        int count = 100;
        float dx = (toWidth - fromWidth) / static_cast<float>(count);
        float dy = (toHeight - fromHeight) / static_cast<float>(count);
        int index = 0;
        float currentWidth = fromWidth;
        float currentHeight = fromHeight;
        TimerUtil::setInterval(3, [to, count, dx, dy, index, currentWidth, currentHeight]() mutable {
            // Update current width and current height
            currentWidth += dx;
            currentHeight += dy;
            index += 1;

            // Resize the window
            to->resize(static_cast<int>(qFloor(currentWidth)), static_cast<int>(qFloor(currentHeight)));

            // Stops if the index == count
            return index == count;
        });
    } else {
        to->show();
    }

    if (from != nullptr) {
        from->close();
    }
}

void WindowUtil::jump(QWidget *from, QWidget *to) {
    WindowUtil::jump(from, to, true);
}

bool WindowUtil::createConfirmationBox(QWidget *parent, const QString &text, const QString &title) {
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(parent, title, text, QMessageBox::Yes | QMessageBox::No);

    return reply == QMessageBox::Yes;
}

bool WindowUtil::createConfirmationBox(QWidget *parent, const QString &text) {
    return createConfirmationBox(parent, text, QString("Confirmation"));
}

void WindowUtil::createErrorMessageBox(QWidget *parent, const QString &errorMessage) {
    QMessageBox::critical(parent, "Error", errorMessage);
}
