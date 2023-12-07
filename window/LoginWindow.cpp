#include "LoginWindow.h"
#include "ui_LoginWindow.h"

#include <QDebug>
#include <QSharedPointer>

#include "windows.h"
#include "utils.h"
#include "constants.h"
#include "Database.h"
#include "LocalUser.h"

LoginWindow::LoginWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoginWindow) {
    ui->setupUi(this);

    setWindowTitle("BudgetWise Login");

    // Click events
    connect(ui->loginButton, SIGNAL(clicked()), this, SLOT(login()));
    connect(ui->signUpButton, SIGNAL(clicked()), this, SLOT(signUp()));
    connect(ui->forgotPasswordButton, SIGNAL(clicked()), this, SLOT(forgotPassword()));

    // Styles
    ui->forgotPasswordButton->setStyleSheet("text-align: left;");
    ui->usernameStatusLabel->setStyleSheet("color: red;");
    ui->passwordStatusLabel->setStyleSheet("color: red;");
}

LoginWindow::LoginWindow(const QString& username, QWidget *parent):
    LoginWindow(parent) {
    ui->usernameInput->setText(username);
    ui->passwordInput->setFocus();
}

LoginWindow::~LoginWindow() {
    delete ui;
}

void LoginWindow::login() {
    // Reset status labels
    ui->usernameStatusLabel->setText("");
    ui->passwordStatusLabel->setText("");

    // Check if the username is empty
    QString username = ui->usernameInput->text();
    if (username == "") {
        return ui->usernameStatusLabel->setText(tr("Username cannot be empty"));
    }

    // Check if the user exists
    UserRepository userRepository = Database::getInstance()->getUserRepository();
    QSharedPointer<User> user(userRepository.getByUsername(username));
    if (user.isNull()) {
        return ui->usernameStatusLabel->setText("User does not exist");
    }

    // Authenticate password
    QString password = ui->passwordInput->text();
    QString authString = user->getAuthString();
    if (!PasswordUtil::match(password, authString, SecretKey::USER_PASSWORD)) {
        return ui->passwordStatusLabel->setText("Incorrect password");
    }

    qDebug() << user->getId() << user->getAuthString();

    // Set local user
    LocalUser::set(user.data());

    // Jump to the main window
    WindowUtil::jump(this, new MainWindow);
}

void LoginWindow::signUp() {
    WindowUtil::jump(this, new SignUpWindow);
}

void LoginWindow::forgotPassword() {
    WindowUtil::jump(this, new ForgotPasswordWindow);
}
