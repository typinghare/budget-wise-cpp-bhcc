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

    /**
     * @brief Creates a question box with "YES" and "NO" buttons.
     * @param parent The parent of the question box.
     * @param text The text to display.
     * @param title The title of the question box.
     * @return true if the user clicked "YES", false if the user clicked "NO".
     */
    static bool createConfirmationBox(QWidget *parent, const QString &text, const QString &title);

    /**
     * @brief Creates a question box with "YES" and "NO" buttons; the title is "Confirmation".
     * @param parent The parent of the question box.
     * @param text The text to display.
     * @return true if the user clicked "YES", false if the user clicked "NO".
     */
    static bool createConfirmationBox(QWidget *parent, const QString &text);

    /**
     * @brief Creates an error message box.
     * @param parent The parentof this error message box.
     * @param errorMessage The error message to display.
     */
    static void createErrorMessageBox(QWidget *parent, const QString &errorMessage);
};


#endif // WINDOWUTIL_H
