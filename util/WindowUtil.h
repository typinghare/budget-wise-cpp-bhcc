#ifndef WINDOWUTIL_H
#define WINDOWUTIL_H

#include <QWidget>

class WindowUtil {
public:
    /**
     * @brief Jumps from one widget to another; close the from window and show the to window.
     * @param from The current widget.
     * @param to The target widget.
     * @param smooth Whether to use smooth transition.
     */
    static void jump(QWidget *from, QWidget *to, bool smooth);

    /**
     * @brief Jumps from one widget to another; close the from window and show the to window.
     * @param from The current widget.
     * @param to The target widget.
     */
    static void jump(QWidget *from, QWidget *to);

};


#endif // WINDOWUTIL_H
