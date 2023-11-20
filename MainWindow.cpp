#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "LoginWindow.h"
#include <QTimer>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
    ui->setupUi(this);

    // Create and show the LoginWindow after a short delay
    QTimer::singleShot(0, this, [this]() {
        auto loginWindow = new LoginWindow();
        loginWindow->show();
        this->close();
    });
}

MainWindow::~MainWindow() {
    delete ui;
}
