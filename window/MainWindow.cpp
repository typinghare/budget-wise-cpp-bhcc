#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QTimer>

#include "windows.h"
#include "utils.h"
#include "Database.h"
#include "LocalUser.h"
#include "windows.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
    ui->setupUi(this);

    // Connect to the database
    Database::getInstance();

    // [TEST]
    LocalUser::set(new User(2, "typinghare", "9;>;9<<{pw|o}vI", "jamechan312.cn@gmail.com"));

    // If local user does not exist, jump to the login window
    QTimer::singleShot(0, this, [this]() {
        if (LocalUser::get() == nullptr) {
            WindowUtil::jump(this, new LoginWindow, false);
        }
    });

    // Set window title
    setWindowTitle("BudgetWise");

    // Events
    connect(ui->checkCategoriesButton, SIGNAL(clicked()), this, SLOT(openCategoryWindow()));
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::openCategoryWindow() {
    WindowUtil::jump(this, new CategoryWindow);
}
