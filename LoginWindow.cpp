#include "LoginWindow.h"
#include "ui_LoginWindow.h"
#include "SignUpWindow.h"
#include "MainWindow.h"

LoginWindow::LoginWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoginWindow) {
    ui->setupUi(this);

    // Click events
    connect(ui->loginButton, SIGNAL(clicked()), this, SLOT(login()));
    connect(ui->signUpButton, SIGNAL(clicked()), this, SLOT(signUp()));
}

LoginWindow::~LoginWindow() {
    delete ui;
}

void LoginWindow::login() {
    auto mainWindow = new MainWindow();
    mainWindow->show();

    close();
}

void LoginWindow::signUp() {
    auto signUpWindow = new SignUpWindow();
    signUpWindow->show();

    close();
}
