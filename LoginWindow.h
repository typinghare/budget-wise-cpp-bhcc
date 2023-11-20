#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QWidget>

namespace Ui {
class LoginWindow;
}

class LoginWindow : public QWidget {
    Q_OBJECT

public:
    explicit LoginWindow(QWidget *parent = nullptr);
    ~LoginWindow();

public slots:
    /**
     * @brief login User logs in.
     */
    void login();

    /**
     * @brief signUp User signs up. The SignUpWindow will show.
     */
    void signUp();

private:
    Ui::LoginWindow *ui;
};

#endif // LOGINWINDOW_H
