#include "SignUpWindow.h"
#include "ui_SignUpWindow.h"

#include <QMessageBox>

#include "windows.h"
#include "utils.h"
#include "constants.h"
#include "Database.h"

SignUpWindow::SignUpWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SignUpWindow) {
    ui->setupUi(this);

    // Connections
    connect(ui->createAccountButton, SIGNAL(clicked()), this, SLOT(signUp()));
    connect(ui->backButton, SIGNAL(clicked()), this, SLOT(back()));

    // Styles
    ui->usernameStatusLabel->setStyleSheet("color: Red;");
    ui->passwordStatusLabel->setStyleSheet("color: Red;");
}

SignUpWindow::~SignUpWindow() {
    delete ui;
}

void SignUpWindow::signUp() {
    // Reset status labels
    ui->usernameStatusLabel->setText("");
    ui->passwordStatusLabel->setText("");

    // Check if the username if empty
    QString username = ui->usernameInput->text();
    if (username == "") {
        return ui->usernameStatusLabel->setText(tr("Username cannot be empty"));
    }

    // Check if the username exists
    UserRepository userRepository = Database::getInstance()->getUserRepository();
    QSharedPointer<User> user(userRepository.getByUsername(username));
    if (!user.isNull()) {
        return ui->usernameStatusLabel->setText(tr("Username already exists"));
    }

    // Check if two passwords are the same
    QString password = ui->passwordInput->text();
    QString confirmPassword = ui->confirmPasswordInput->text();
    if (password != confirmPassword) {
        return ui->passwordStatusLabel->setText(tr("Two passwords are not the same!"));
    }

    // Sign up
    QString email = ui->emailInput->text();
    QString authString = PasswordUtil::encrypt(password, SecretKey::USER_PASSWORD);
    User* newUser = userRepository.create(username, authString, email);
    if (newUser == nullptr) {
        qDebug() << "Fail to sign up.";
    } else {
        QMessageBox::information(this, "Success", "You created an account successfully!");
    }

    // Jump to the main window
    WindowUtil::jump(this, new LoginWindow(username));
}

void SignUpWindow::back() {
    WindowUtil::jump(this, new LoginWindow);
}
