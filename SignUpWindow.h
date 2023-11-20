#ifndef SIGNUPWINDOW_H
#define SIGNUPWINDOW_H

#include <QWidget>

namespace Ui {
class SignUpWindow;
}

class SignUpWindow : public QWidget {
    Q_OBJECT

public:
    explicit SignUpWindow(QWidget *parent = nullptr);
    ~SignUpWindow();

public slots:
    /**
     * @brief signUp User signs up.
     */
    void signUp();

private:
    Ui::SignUpWindow *ui;
};

#endif // SIGNUPWINDOW_H
