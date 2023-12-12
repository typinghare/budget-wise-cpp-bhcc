#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QTimer>
#include <QMenuBar>
#include <QMenu>
#include <QSharedPointer>

#include "src/windows.h"
#include "src/utils.h"
#include "src/services.h"
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

    createRecordDialog = new QDialog(this);
    createRecordWindow = new CreateRecordWindow(createRecordDialog);
    createRecordWindow->show();
    createRecordDialog->resize(createRecordWindow->width(), createRecordWindow->height());
    createRecordDialog->setModal(true);

    // Events
    connect(ui->manageCategoriesButton, &QPushButton::clicked, this, &MainWindow::openCategoryWindow);
    connect(ui->manageSubcategoriesButton, &QPushButton::clicked, this, &MainWindow::openSubcategoryWindow);
    connect(ui->addButton, &QPushButton::clicked, this, &MainWindow::onAddButtonClicked);
    connect(createRecordWindow, &CreateRecordWindow::confirmed, this, &MainWindow::onCreateConfirmed);
    connect(createRecordWindow, &CreateRecordWindow::canceled, this, &MainWindow::onCreateCanceled);

    // Create menu
    createMenu();

    // If local user does not exist, jump to the login window
    QTimer::singleShot(0, this, [this]() {
        if (LocalUser::get() == nullptr) {
            WindowUtil::jump(this, new LoginWindow, false);
        }
    });

    // Load and display records
    loadRecords();
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
    logoutActioin = new QAction(tr("&Logout"), this);
    userMenu->addAction(logoutActioin);
    connect(logoutActioin, &QAction::triggered, this, &MainWindow::logout);
}

void MainWindow::loadRecords() {
    unsigned int userId = LocalUser::get()->getId();
    RecordService recordService;
    QList<Record*> recordList = recordService.getAllRecords(userId);

    // createRecordWindow->setSubcategories();

    // Delete list
    recordList.clear();
}

void MainWindow::openCategoryWindow() {
    WindowUtil::jump(this, new CategoryWindow);
}

void MainWindow::openSubcategoryWindow() {
    WindowUtil::jump(this, new SubcategoryWindow(""));
}

void MainWindow::logout() {
    QString username = LocalUser::get()->getUsername();
    LocalUser::set(nullptr);

    logoutActioin->setDisabled(true);

    WindowUtil::jump(this, new LoginWindow(username));
}

void MainWindow::onAddButtonClicked() {
    createRecordDialog->setWindowTitle("Create Record");
    createRecordDialog->exec();
}

void MainWindow::onCreateConfirmed(unsigned int categoryId, float amount) {
    createRecordDialog->close();

    auto subcategoryRepository = Database::getInstance()->getSubcategoryRepository();
    // QSharedPointer<Subcategory> subcategory(subcategoryRepository.getByUserIdAndCategoryIdAndName(
    //     subcategoryName));
}

void MainWindow::onCreateCanceled() {
    createRecordDialog->close();
}
