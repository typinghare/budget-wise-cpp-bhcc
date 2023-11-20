#include "SignUpWindow.h"
#include "ui_SignUpWindow.h"
#include <QDebug>
#include "MainWindow.h"
#include "util/WindowUtil.h"

SignUpWindow::SignUpWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SignUpWindow) {
    ui->setupUi(this);

    ui->passwordInput->setEchoMode(QLineEdit::Password);
    ui->confirmPasswordInput->setEchoMode(QLineEdit::Password);

    // Connections
    connect(ui->createAccountButton, SIGNAL(clicked()), this, SLOT(signUp()));
}

SignUpWindow::~SignUpWindow() {
    delete ui;
}

void SignUpWindow::signUp() {
    QString username = ui->usernameInput->text();
    QString password = ui->passwordInput->text();
    QString confirmPassword = ui->confirmPasswordInput->text();

    // Check if two passwords are the same
    if (password != confirmPassword) {
        ui->statusLabel->setText(tr("Two passwords are not the same!"));
        return;
    }

    // Send a sign up request to the backend
    qDebug() << username;

    // Navigate to the main window
    WindowUtil::navigate(this, new MainWindow, true);
}
