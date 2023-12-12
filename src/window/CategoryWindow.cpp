#include "CategoryWindow.h"
#include "ui_CategoryWindow.h"

#include <QDebug>
#include <QMessageBox>
#include <QSharedPointer>

#include "src/utils.h"
#include "src/windows.h"
#include "src/LocalUser.h"
#include "src/Database.h"

CategoryWindow::CategoryWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CategoryWindow),
    itemModel(new QStandardItemModel(this)),
    updateIndex(-1) {
    ui->setupUi(this);

    updateCategoryDialog = new QDialog(this);
    updateCategoryWindow = new UpdateCategoryWindow(updateCategoryDialog);
    updateCategoryWindow->show();
    updateCategoryDialog->resize(updateCategoryWindow->width(), updateCategoryWindow->height());
    updateCategoryDialog->setModal(true);

    // Title
    setWindowTitle("Category Management - BudgetWise");

    // Events
    connect(ui->addButton, &QPushButton::clicked, this, &CategoryWindow::onAddButtonClicked);
    connect(ui->updateButton, &QPushButton::clicked, this, &CategoryWindow::onUpdateButtonClicked);
    connect(ui->deletButton, &QPushButton::clicked, this, &CategoryWindow::deleteSelectedCategory);
    connect(ui->backButton, &QPushButton::clicked, this, &CategoryWindow::back);
    connect(updateCategoryWindow, &UpdateCategoryWindow::categoryNameConfirmed,
            this, &CategoryWindow::onUpdateConfirmed);

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
        QSharedPointer<Category> category(categoryList.at(row));
        QString categoryName = category->getName();
        itemModel->setItem(row, 0, new QStandardItem(categoryName));
    }

    ui->categoryTable->setModel(itemModel);

    // On selected
    connect(ui->categoryTable->selectionModel(), &QItemSelectionModel::selectionChanged,
            this, &CategoryWindow::onItemSelected);

    // On double clicked
    connect(ui->categoryTable, &QAbstractItemView::doubleClicked, this, &CategoryWindow::onTableDoubleClicked);

    // Delete category list
    categoryList.clear();
}

void CategoryWindow::onAddButtonClicked() {
    // Reset the update index
    updateIndex = -1;

    // Set the category name
    updateCategoryWindow->setCategoryName("");

    updateCategoryDialog->setWindowTitle("Add Category");
    updateCategoryDialog->exec();
}

void CategoryWindow::onUpdateButtonClicked() {
    if (selectedIndexes.isEmpty()) {
        showStatusMessage("You must select a category first!", "red");
        return;
    }

    if (selectedIndexes.size() > 1) {
        showStatusMessage("You must select only one category!", "red");
        return;
    }

    updateIndex = *selectedIndexes.begin();

    // Set the category name
    QString categoryName = itemModel->item(updateIndex, 0)->data(Qt::DisplayRole).toString();
    updateCategoryWindow->setCategoryName(categoryName);

    updateCategoryDialog->setWindowTitle("Update Category");
    updateCategoryDialog->exec();
}

void CategoryWindow::onUpdateConfirmed(const QString& categoryName) {
    // Close the update category dialog
    updateCategoryDialog->close();

    // If the category name is an empty string, cut off the process
    if (categoryName == "") {
        return;
    }

    if (updateIndex == -1) {
        addCategory(categoryName);
    } else {
        updateCategory(categoryName);
    }
}

void CategoryWindow::addCategory(const QString &categoryName) {
    // Get the local user's ID
    int userId = LocalUser::get()->getId();

    // Check whether the category exists
    auto categoryRepository = Database::getInstance()->getCategoryRepository();
    QSharedPointer<Category> category(categoryRepository.getByUserIdAndName(userId, categoryName));
    if (!category.isNull()) {
        return WindowUtil::createErrorMessageBox(this, "The category already exists.");
    }

    // Create a category
    QSharedPointer<Category> newCategory(categoryRepository.create(userId, categoryName));
    if (newCategory.isNull()) {
        qDebug() << "Fail to create the category.";
    }

    // Append the catgory to the list
    itemModel->setItem(itemModel->rowCount(), 0, new QStandardItem(categoryName));

    // Show status message
    showStatusMessage("You added an category successfully!", "green");
}

void CategoryWindow::updateCategory(const QString &categoryName) {
    // Get the local user's ID
    int userId = LocalUser::get()->getId();

    // Check whether the category exists
    auto categoryRepository = Database::getInstance()->getCategoryRepository();
    QSharedPointer<Category> category(categoryRepository.getByUserIdAndName(userId, categoryName));
    if (!category.isNull()) {
        return WindowUtil::createErrorMessageBox(this, "The category already exists!");
    }

    // Get the original category
    QString originalCategoryName
        = itemModel->item(updateIndex, 0)->data(Qt::DisplayRole).toString();
    QSharedPointer<Category> categoryToUpdate(categoryRepository.getByUserIdAndName(userId, originalCategoryName));
    if (categoryToUpdate.isNull()) {
        return WindowUtil::createErrorMessageBox(this, "The category to update does not exist!");
    }

    // Update the category
    bool updateResult = categoryRepository.update(categoryToUpdate->getId(), categoryName);
    if (!updateResult) {
        qDebug() << "Fail to update the category.";
    }

    // Update the row; reset the update index
    itemModel->setItem(updateIndex, 0, new QStandardItem(categoryName));
    updateIndex = -1;

    // Show status message
    showStatusMessage("You updated the category successfully!", "green");
}

void CategoryWindow::onItemSelected(const QItemSelection &selected, const QItemSelection &deselected) {
    for (const QModelIndex &index : selected.indexes()) {
        selectedIndexes.insert(index.row());
    }

    for (const QModelIndex &index : deselected.indexes()) {
        selectedIndexes.remove(index.row());
    }
}

void CategoryWindow::deleteSelectedCategory() {
    // Check if no categories are selected
    if (selectedIndexes.isEmpty()) {
        showStatusMessage("No selected categories to delete..", "red");
    }

    // Confirm the deletion
    QString numSelectedCategory = QString::number(selectedIndexes.size());
    QString text = "Are you sure to delete the selected " + numSelectedCategory + " categories?";
    bool confirmed = WindowUtil::createConfirmationBox(this, text);
    if (!confirmed) {
        return;
    }

    // Get the local user's ID
    int userId = LocalUser::get()->getId();

    auto categoryRepository = Database::getInstance()->getCategoryRepository();
    QList<int> deletedRows;
    for (QSet<int>::const_iterator it = selectedIndexes.constBegin(); it != selectedIndexes.constEnd(); ++it) {
        int row = *it;
        deletedRows.append(row);

        QStandardItem* item = itemModel->item(row, 0);
        QString categoryName = item->data(Qt::DisplayRole).toString();

        // Remove the category
        bool removeResult = categoryRepository.remove(userId, categoryName);
        if (!removeResult) {
            continue;
        }

        // Remove all related subcategories
        QSharedPointer<Category> category(categoryRepository.getByUserIdAndName(userId, categoryName));
        if (!category.isNull()) {
            unsigned int categoryId = category->getId();
            auto subcategoryRepository = Database::getInstance()->getSubcategoryRepository();
            subcategoryRepository.removeByCategoryId(userId, categoryId);
        }
    }

    // Remove the rows from the table view
    itemModel->removeRows(deletedRows.first(), deletedRows.size());

    // Show status message
    showStatusMessage("You deleted " + numSelectedCategory + " categories!", "green");
}

void CategoryWindow::back() {
    WindowUtil::jump(this, new MainWindow);
}

void CategoryWindow::showStatusMessage(const QString& message, const QString& color) {
    ui->statusLabel->setStyleSheet("color:" + color + ";");
    ui->statusLabel->setText(message);
    TimerUtil::setTimeout(3000, [this]() {
        ui->statusLabel->setText("");
    });
}

void CategoryWindow::onTableDoubleClicked(const QModelIndex &index) {
    if (!index.isValid()) {
        return;
    }

    int rowIndex = index.row();
    if (rowIndex < 0) {
        return;
    }

    // Check category name
    auto categoryName = itemModel->item(rowIndex, 0)->data(Qt::DisplayRole).toString();
    if (categoryName == "") {
        return;
    }
    qDebug() << rowIndex;

    // Jump to the subcategory window
    WindowUtil::jump(this, new SubcategoryWindow(categoryName));
}
