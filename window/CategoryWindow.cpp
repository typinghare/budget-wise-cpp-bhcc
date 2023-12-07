#include "CategoryWindow.h"
#include "ui_CategoryWindow.h"

#include <QDebug>
#include <QMessageBox>

#include "utils.h"
#include "windows.h"
#include "LocalUser.h"
#include "Database.h"

CategoryWindow::CategoryWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CategoryWindow),
    itemModel(new QStandardItemModel(this)){
    ui->setupUi(this);

    updateCategoryDialog = new QDialog(this);
    updateCategoryWindow = new UpdateCategoryWindow(updateCategoryDialog);
    updateCategoryDialog->resize(updateCategoryWindow->width(), updateCategoryWindow->height());

    setWindowTitle("Category Management - BudgetWise");

    // Events
    connect(ui->addButton, SIGNAL(clicked()), this, SLOT(addCategory()));
    connect(ui->updateButton, SIGNAL(clicked()), this, SLOT(updateSelectedCategory()));
    connect(ui->deletButton, SIGNAL(clicked()), this, SLOT(deleteSelectedCategory()));
    connect(ui->backButton, SIGNAL(clicked()), this, SLOT(back()));
    connect(updateCategoryWindow, SIGNAL(categoryNameConfirmed(QString)),
            this, SLOT(onCategoryNameConfirmed(QString)));

    // Display categories
    displayCategories();
}

CategoryWindow::~CategoryWindow() {
    delete ui;
}

void CategoryWindow::displayCategories() {
    // Get the local user's ID
    int userId = LocalUser::get()->getId();

    // Retrieve all categories from the database
    auto categoryRepository = Database::getInstance()->getCategoryRepository();
    auto categoryList = categoryRepository.getAll(userId);

    // Table header
    itemModel->setHorizontalHeaderLabels(QStringList() << "Name");

    // Table rows
    for (int row = 0; row < categoryList.size(); ++row) {
        QString categoryName = categoryList.at(row)->getName();
        itemModel->setItem(row, 0, new QStandardItem(categoryName));
    }

    ui->categoryTable->setModel(itemModel);

    // On selected
    connect(ui->categoryTable->selectionModel(), &QItemSelectionModel::selectionChanged,
            this, &CategoryWindow::onItemSelected);
}

void CategoryWindow::addCategory() {
    // Open the update category dialog
    updateCategoryWindow->show();
    updateCategoryDialog->setModal(true);
    updateCategoryDialog->exec();
}

void CategoryWindow::onCategoryNameConfirmed(const QString& categoryName) {
    qDebug() << "onCategoryNameConfirmed";

    // Close the update category dialog
    updateCategoryDialog->close();

    // If the category name is an empty string, cut off the process
    if (categoryName == "") {
        return;
    }

    // Get the local user's ID
    int userId = LocalUser::get()->getId();

    // Check whether the category exists
    auto categoryRepository = Database::getInstance()->getCategoryRepository();
    auto category = categoryRepository.getByUserIdAndName(userId, categoryName);
    if (category != nullptr) {
        QMessageBox::critical(this, "Error", "The category already exists.");
        return;
    }

    // Create a category
    category = categoryRepository.createCategory(userId, categoryName);
    if (category == nullptr) {
        qDebug() << "Fail to create the category.";
    } else {
        // Append the catgory to the list
        itemModel->setItem(itemModel->rowCount(), 0, new QStandardItem(categoryName));

        QMessageBox::information(this, "Success", "You added an category successfully!");
    }
}

void CategoryWindow::onItemSelected(const QItemSelection &selected, const QItemSelection &deselected) {
    for (const QModelIndex &index : selected.indexes()) {
        selectedIndexes.insert(index.row());
    }

    for (const QModelIndex &index : deselected.indexes()) {
        selectedIndexes.remove(index.row());
    }
}

void CategoryWindow::updateSelectedCategory() {
    if (selectedIndexes.size() > 1) {
        QMessageBox::critical(this, "Error", "Please select only one category.");
        return;
    }
}

void CategoryWindow::deleteSelectedCategory() {
    // Get the local user's ID
    int userId = LocalUser::get()->getId();

    auto categoryRepository = Database::getInstance()->getCategoryRepository();
    for (const int &row : selectedIndexes) {
        QStandardItem* cellItem = itemModel->item(row, 0);
        QVariant cellData = cellItem->data(Qt::DisplayRole);
        QString categoryName = cellData.toString();
        categoryRepository.remove(userId, categoryName);

        // Remove it from the table
    }
}

void CategoryWindow::back() {
    WindowUtil::jump(this, new MainWindow);
}
