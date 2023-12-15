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
#include "src/Dummy.h"

MainWindow::MainWindow(QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    itemModel(new QStandardItemModel(this)) {
    ui->setupUi(this);

    // Connect to the database
    Database::getInstance();

    // [TEST]
    // LocalUser::set(new User(1, "TypingHare", "9;>;9<<{pw|o}vI", "jamechan312.cn@gmail.com"));

    // Create fake records for USER #1
    // Dummy::makeDummyRecords();

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
    connect(ui->deleteLastButton, &QPushButton::clicked, this, &MainWindow::onDeleteLastButtonClicked);
    connect(createRecordWindow, &CreateRecordWindow::confirmed, this, &MainWindow::onCreateConfirmed);
    connect(createRecordWindow, &CreateRecordWindow::canceled, this, &MainWindow::onCreateCanceled);
    connect(ui->viewButton, &QPushButton::clicked, this, &MainWindow::onViewButtonClicked);

    // Create menu
    createMenu();

    // If local user does not exist, jump to the login window
    QTimer::singleShot(0, this, [this]() {
        if (LocalUser::get() == nullptr) {
            WindowUtil::jump(this, new LoginWindow, false);
        }
    });

    // Load user's current balance
    loadCurrentBalance();

    if (LocalUser::get() != nullptr) {
        // Load subcategories and add them to the create record window
        loadSubcategories();

        // Load and display records
        loadRecords();
    }
}

MainWindow::~MainWindow() {
    delete ui;
    delete createRecordDialog;
    delete itemModel;
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

void MainWindow::loadSubcategories() {
    auto userId = LocalUser::get()->getId();
    auto subcategoryRepository = Database::getInstance()->getSubcategoryRepository();
    auto subcategoryList = subcategoryRepository.getAllByUserId(userId);

    // Set map
    auto categoryRepository = Database::getInstance()->getCategoryRepository();
    for (auto &subcategory: subcategoryList) {
        auto categoryId = subcategory->getCategoryId();
        auto subcategoryName = subcategory->getName();
        if (categoryIdMap.contains(categoryId)) {
        } else {
            QSharedPointer<Category>category(categoryRepository.get(categoryId));
            if (category.isNull()) {
                continue;
            }

            categoryIdMap[categoryId] = category->getName();
        }

        subcategoryIdMap[subcategory->getId()] = subcategoryName;
    }

    // Delete list
    subcategoryList.clear();
}

void MainWindow::loadRecords() {
    itemModel->clear();

    unsigned int userId = LocalUser::get()->getId();

    // Table header
    itemModel->setHorizontalHeaderLabels(QStringList() << "Date" << "Category" << "Subcategory" << "Amount" << "Balance");
    ui->recordTable->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

    // Display all records
    RecordService recordService;
    QList<Record*> recordList = recordService.getAllRecords(userId, false);
    for (Record* &record : recordList) {
        QDateTime createdAt = record->getCreatedAt();
        unsigned int categoryId = record->getCategoryId();
        unsigned int subcategoryId = record->getSubcategoryId();
        double amount = record->getAmount();
        double balance = record->getBalance();
        QString subcategoryName = subcategoryIdMap[subcategoryId];
        QString categoryName = categoryIdMap[categoryId];

        setRow(itemModel->rowCount(), createdAt, categoryName, subcategoryName, amount, balance);
    }

    ui->recordTable->setModel(itemModel);

    // Delete record list
    recordList.clear();
}

void MainWindow::loadCurrentBalance() {
    if (LocalUser::get() == nullptr) {
        return setBalance(0);
    }

    auto userId = LocalUser::get()->getId();
    auto recordRepository = Database::getInstance()->getRecordRepository();
    auto lastRecordId = recordRepository.getLastId(userId);
    if (lastRecordId == 0) {
        return setBalance(0);
    }

    QSharedPointer<Record> record(recordRepository.getWithBalance(lastRecordId));
    if (record.isNull()) {
        return setBalance(0);
    }

    setBalance(record->getBalance());
}

void MainWindow::setBalance(double balance) {
    if (balance == 0) {
        ui->balanceLabel->setStyleSheet("color: black");
    } else if (balance < 0) {
        ui->balanceLabel->setStyleSheet("color: red");
    } else {
        // balance > 0
        ui->balanceLabel->setStyleSheet("color: green");
    }

    ui->balanceLabel->setText("$ " + QString::number(balance, 'f', 2));
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
    createRecordWindow->refreshCategories();
    if (createRecordWindow->getCategoryCount() == 0) {
        return WindowUtil::createErrorMessageBox(this, "You don't have a category yet!");
    }

    createRecordDialog->setWindowTitle("Create Transaction");
    createRecordDialog->exec();
}

void MainWindow::onDeleteLastButtonClicked() {
    // Check if the record exists
    if (itemModel->rowCount() == 0) {
        return WindowUtil::createErrorMessageBox(this, "There are no transactions to delete!");
    }

    // Ask the user to confirm
    bool confirmed = WindowUtil::createConfirmationBox(this, "Do you really want to delete the last transaction?");
    if (!confirmed) {
        return;
    }

    auto userId = LocalUser::get()->getId();
    RecordService recordService;
    bool result = recordService.deleteLastRecord(userId);
    if (!result) {
        WindowUtil::createErrorMessageBox(this, "Fail to delete the last transaction!");
    }

    itemModel->removeRow(itemModel->rowCount() - 1);
    QString balance = itemModel->item(itemModel->rowCount() - 1, 4)->data(Qt::DisplayRole).toString();
    setBalance(balance.toDouble());
}

void MainWindow::onViewButtonClicked() {
    WindowUtil::jump(this, new ViewWindow);
}

void MainWindow::onCreateConfirmed(unsigned int categoryId, unsigned int subcategoryId, double amount) {
    createRecordDialog->close();

    auto userId = LocalUser::get()->getId();

    if (subcategoryId == 0) {
        // Get the category
        auto categoryRepository = Database::getInstance()->getCategoryRepository();
        QSharedPointer<Category> category(categoryRepository.get(categoryId));
        if (category.isNull()) {
            return WindowUtil::createErrorMessageBox(this, "The category does not exist!");
        }

        // Ask the user to confirm
        QString signStr(amount > 0 ? "+" : "");
        QString desc(category->getName() + " " + signStr + QString::number(amount, 'f', 2));
        QString message("Do you want to add this transaction?\n\n  " + desc + "\n\nYou can not update your transaction.");
        bool confirmed = WindowUtil::createConfirmationBox(this, message);
        if (!confirmed) {
            return;
        }
    } else {
        // Get the subcategory
        auto subcategoryRepository = Database::getInstance()->getSubcategoryRepository();
        QSharedPointer<Subcategory> subcategory(subcategoryRepository.get(subcategoryId));
        if (subcategory.isNull()) {
            return WindowUtil::createErrorMessageBox(this, "The subcategory does not exist!");
        }

        // Ask the user to confirm
        QString signStr(amount > 0 ? "+" : "");
        QString desc(subcategory->getName() + " " + signStr + QString::number(amount, 'f', 2));
        QString message("Do you want to add this transaction?\n\n  " + desc + "\n\nYou can not update your transaction.");
        bool confirmed = WindowUtil::createConfirmationBox(this, message);
        if (!confirmed) {
            return;
        }
    }

    // Create
    RecordService recordService;
    auto record = recordService.createRecord(userId, categoryId, subcategoryId, amount);
    if (record.isNull()) {
        return WindowUtil::createErrorMessageBox(this, "Fail to create the record!");
    }

    setRow(
        itemModel->rowCount(),
        record->getCreatedAt(),
        categoryIdMap[categoryId],
        subcategoryIdMap[subcategoryId],
        amount,
        record->getBalance());

    // Update balance
    setBalance(record->getBalance());
}

void MainWindow::onCreateCanceled() {
    createRecordDialog->close();
}

void MainWindow::setRow(
    int row,
    QDateTime createdAt,
    const QString& categoryName,
    const QString& subcategoryName,
    double amount,
    double balance) {
    itemModel->setItem(row, 0, new QStandardItem(createdAt.toString("MM/dd/yyyy")));
    itemModel->setItem(row, 1, new QStandardItem(categoryName));
    itemModel->setItem(row, 2, new QStandardItem(subcategoryName));
    itemModel->setItem(row, 3, new QStandardItem(QString::number(amount, 'f', 2)));
    itemModel->setItem(row, 4, new QStandardItem(QString::number(balance, 'f', 2)));
}

void MainWindow::unshiftRow(
    QDateTime createdAt,
    const QString &categoryName,
    const QString &subcategoryName,
    double amount,
    double balance) {
    QList<QStandardItem*> newRowItems;
    newRowItems.append(new QStandardItem(createdAt.toString("MM/dd/yyyy")));
    newRowItems.append(new QStandardItem(categoryName));
    newRowItems.append(new QStandardItem(subcategoryName));
    newRowItems.append(new QStandardItem(QString::number(amount, 'f', 2)));
    newRowItems.append(new QStandardItem(QString::number(balance, 'f', 2)));

    itemModel->insertRow(0, newRowItems);
}
