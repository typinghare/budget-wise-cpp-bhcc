#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QWidget>

namespace Ui { class LoginWindow; }

class LoginWindow : public QWidget {
    Q_OBJECT

public:
    explicit LoginWindow(QWidget *parent = nullptr);
    explicit LoginWindow(const QString& username, QWidget *parent = nullptr);
    ~LoginWindow();

public slots:
    /**
     * @brief login User logs in.
     */
    void login();

    /**
     * @brief signUp User signs up; navigates to the sign up window.
     */
    void signUp();

    /**
     * @brief Navigate to the forget password window.
     */
    void forgotPassword();

private:
    Ui::LoginWindow *ui;
};

#endif // LOGINWINDOW_H
