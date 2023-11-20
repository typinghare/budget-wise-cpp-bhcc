#include "WindowUtil.h"

void WindowUtil::navigate(QWidget *from, QWidget *to, bool closeCurrentWidget) {
    if (from != nullptr) {
        if (closeCurrentWidget) {
            from->close();
        } else {
            from->hide();
        }
    }

    if (to != nullptr) {
        to->show();
    }
}

void WindowUtil::navigate(QWidget *from, QWidget *to) {
    WindowUtil::navigate(from, to, true);
}
