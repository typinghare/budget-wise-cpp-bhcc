#include "ForgotPasswordWindow.h"
#include "ui_ForgotPasswordWindow.h"

#include <QSharedPointer>

#include "src/windows.h"
#include "src/utils.h"
#include "src/Database.h"
#include "src/constants.h"


ForgotPasswordWindow::ForgotPasswordWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ForgotPasswordWindow) {
    ui->setupUi(this);

    setWindowTitle("Forgot Passowrd - BudgetWise");

    // Click events
    connect(ui->resetPassword, SIGNAL(clicked()), this, SLOT(resetPassword()));
    connect(ui->backButton, SIGNAL(clicked()), this, SLOT(back()));

    // Styles
    ui->usernameStatusLabel->setStyleSheet("color: red;");
    ui->emailStatusLabel->setStyleSheet("color: red;");
    ui->passwordStatusLabel->setStyleSheet("color: red;");

    // Tab order
    ui->usernameInput->setFocus();
    setTabOrder(ui->usernameInput, ui->emailInput);
    setTabOrder(ui->emailInput, ui->passwordInput);
    setTabOrder(ui->passwordInput, ui->confirmPasswordInput);
}

ForgotPasswordWindow::~ForgotPasswordWindow() {
    delete ui;
}

void ForgotPasswordWindow::resetPassword() {
    // Reset status labels
    ui->usernameStatusLabel->setText("");
    ui->emailStatusLabel->setText("");
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

    // Check if the email is empty
    QString email = ui->emailInput->text();
    if (email == "") {
        return ui->emailStatusLabel->setText(tr("Email cannot be empty"));
    }

    // Check if the email matches
    if (email != user->getEmail()) {
        return ui->emailStatusLabel->setText(tr("Email does not match the username"));
    }

    // Check if the length of the password is larger than six
    QString password = ui->passwordInput->text();
    if (password.size() <= 6) {
        return ui->passwordStatusLabel->setText("Password must be longer than six");
    }

    // Check if two passwords are the same
    QString confirmPassword = ui->confirmPasswordInput->text();
    if (password != confirmPassword) {
        return ui->passwordStatusLabel->setText(tr("Two passwords are not the same"));
    }

    // Update password
    QString authString = PasswordUtil::encrypt(password, SecretKey::USER_PASSWORD);
    bool updateResult = userRepository.updateAuthString(user->getId(), authString);
    if (!updateResult) {
        qDebug() << "Fail to sign up.";
    }

    WindowUtil::jump(this, new LoginWindow(username));
}

void ForgotPasswordWindow::back() {
    WindowUtil::jump(this, new LoginWindow);
}
