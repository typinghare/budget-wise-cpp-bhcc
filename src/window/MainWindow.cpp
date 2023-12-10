#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QTimer>
#include <QMenuBar>
#include <QMenu>

#include "src/windows.h"
#include "src/utils.h"
#include "src/Database.h"
#include "src/LocalUser.h"
#include "src/windows.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
    ui->setupUi(this);

    // Connect to the database
    Database::getInstance();

    // [TEST]
    LocalUser::set(new User(2, "typinghare", "9;>;9<<{pw|o}vI", "jamechan312.cn@gmail.com"));

    // Set window title
    setWindowTitle("BudgetWise");

    // Events
    connect(ui->manageCategoriesButton, SIGNAL(clicked()), this, SLOT(openCategoryWindow()));
    connect(ui->manageSubcategoriesButton, SIGNAL(clicked()), this, SLOT(openSubcategoryWindow()));

    // Create menu
    createMenu();

    // If local user does not exist, jump to the login window
    QTimer::singleShot(0, this, [this]() {
        if (LocalUser::get() == nullptr) {
            WindowUtil::jump(this, new LoginWindow, false);
        }
    });
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::createMenu() {
    // Create a menu bar
    QMenuBar *menuBar = new QMenuBar(this);
    setMenuBar(menuBar);

    // Create a user menu
    QMenu *userMenu = menuBar->addMenu(tr("&User"));
    QAction *logoutActioin = new QAction(tr("&Logout"), this);
    connect(logoutActioin, &QAction::triggered, this, &MainWindow::logout);
    userMenu->addAction(logoutActioin);

    qDebug() << "create";
}

void MainWindow::openCategoryWindow() {
    WindowUtil::jump(this, new CategoryWindow);
}

void MainWindow::openSubcategoryWindow() {
    WindowUtil::jump(this, new SubcategoryWindow(""));
}

void MainWindow::logout() {
    LocalUser::set(nullptr);
    WindowUtil::jump(this, new LoginWindow);
}
