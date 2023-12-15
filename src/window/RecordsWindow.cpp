#include "RecordsWindow.h"
#include "ui_RecordsWindow.h"

#include <QSharedPointer>

#include "src/utils.h"
#include "src/windows.h"
#include "src/Database.h"
#include "src/LocalUser.h"

RecordsWindow::RecordsWindow(QWidget *parent):
    QWidget(parent),
    ui(new Ui::RecordsWindow),
    itemModel(new QStandardItemModel(this)),
    categoryId(0) {
    ui->setupUi(this);

    // Title
    setWindowTitle("Records - BudgetWise");

    connect(ui->backButton, &QPushButton::clicked, this, &RecordsWindow::onBackButtonClicked);
}

RecordsWindow::RecordsWindow(const QString &categoryName, QWidget *parent):
    RecordsWindow(parent) {
    // Get the category ID
    auto userId = LocalUser::get()->getId();
    auto categoryRepository = Database::getInstance()->getCategoryRepository();
    QSharedPointer<Category> category(categoryRepository.getByUserIdAndName(userId, categoryName));
    if (category.isNull()) {
        categoryId = 0;
    } else {
        setWindowTitle("Transactions of " + categoryName);
        categoryId = category->getId();
    }

    displayRecords();
}

RecordsWindow::~RecordsWindow() {
    delete ui;
    delete itemModel;
}

void RecordsWindow::displayRecords() {
    // Table headers
    itemModel->setHorizontalHeaderLabels(QStringList() << "Date" << "Subcategory" << "Amount");
    ui->recordTable->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

    ui->recordTable->setModel(itemModel);

    // Load records
    double total = 0.0;
    if (categoryId != 0) {
        auto recordRepository = Database::getInstance()->getRecordRepository();
        auto subcategoryRespository = Database::getInstance()->getSubcategoryRepository();
        auto recordList = recordRepository.getAllByCategory(categoryId, false);
        for (auto &record : recordList) {
            QDateTime createdAt = record->getCreatedAt();
            unsigned int subcategoryId = record->getSubcategoryId();
            double amount = record->getAmount();
            QSharedPointer<Subcategory> subcategory(subcategoryRespository.get(subcategoryId));
            QString subcategoryName = subcategory.isNull() ? "" :subcategory->getName();

            setRow(itemModel->rowCount(), createdAt, subcategoryName, amount);

            total += amount;
        }
    }

    // Set total
    ui->totalNumberLabel->setText("$ " + QString::number(total, 'f', 2));
}

void RecordsWindow::onBackButtonClicked() {
    WindowUtil::jump(this, new CategoryWindow);
}

void RecordsWindow::setRow(
    int row,
    QDateTime date,
    const QString& subcategoryName,
    double amount) {
    itemModel->setItem(row, 0, new QStandardItem(date.toString("MM/dd/yyyy")));
    itemModel->setItem(row, 1, new QStandardItem(subcategoryName));
    itemModel->setItem(row, 2, new QStandardItem(QString::number(amount, 'f', 2)));
}
