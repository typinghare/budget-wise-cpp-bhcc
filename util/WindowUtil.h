#ifndef WINDOWUTIL_H
#define WINDOWUTIL_H

#include <QWidget>

namespace WindowUtil {

/**
 * @brief Navigates from one widget to another.
 * @param from The current widget.
 * @param to The target widget.
 * @param closeCurrentWidget Close the current widget if true is given; hide otherwise.
 */
void navigate(QWidget *from, QWidget *to, bool closeCurrentWidget);

/**
 * @brief Navigates from one widget to another; closes the current widget.
 * @param from The current widget.
 * @param to The target widget.
 */
void navigate(QWidget *from, QWidget *to);

}


#endif // WINDOWUTIL_H
