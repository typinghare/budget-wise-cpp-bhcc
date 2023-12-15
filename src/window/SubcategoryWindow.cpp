#include "SubcategoryWindow.h"
#include "ui_SubcategoryWindow.h"

#include <QMap>
#include <QMessageBox>
#include <QSharedPointer>

#include "src/utils.h"
#include "src/windows.h"
#include "src/Database.h"
#include "src/LocalUser.h"
#include "src/service/SubcategoryService.h"

SubcategoryWindow::SubcategoryWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SubcategoryWindow),
    itemModel(new QStandardItemModel(this)),
    updateIndex(-1),
    fromCategoryWindow(false) {
    ui->setupUi(this);

    updateSubcategoryDialog = new QDialog(this);
    updateSubcategoryWindow = new UpdateSubcategoryWindow(updateSubcategoryDialog);
    updateSubcategoryWindow->show();
    updateSubcategoryDialog->resize(updateSubcategoryWindow->width(), updateSubcategoryWindow->height());
    updateSubcategoryDialog->setModal(true);

    // Title
    setWindowTitle("Subcategory Management - BudgetWise");

    // Events
    connect(ui->addButton, &QPushButton::clicked, this, &SubcategoryWindow::onAddbuttonClicked);
    connect(ui->updateButton, &QPushButton::clicked, this, &SubcategoryWindow::onUpdateButtonClicked);
    connect(ui->deleteButton, &QPushButton::clicked, this, &SubcategoryWindow::onDeleteButtonClicked);
    connect(ui->backButton, &QPushButton::clicked, this, &SubcategoryWindow::onBackButtonClicked);
    connect(updateSubcategoryWindow, &UpdateSubcategoryWindow::confirmed,
            this, &SubcategoryWindow::onUpdateConfirmed);

    // Initializes categories
    auto userId = LocalUser::get()->getId();
    auto categoryRepository = Database::getInstance()->getCategoryRepository();
    auto categoryList = categoryRepository.getAll(userId);
    QList<QString> categoryNameList;
    for (const auto &category: categoryList) {
        categoryNameList.append(category->getName());
    }
    updateSubcategoryWindow->setCategoryNames(categoryNameList);
}

SubcategoryWindow::SubcategoryWindow(const QString& categoryName, QWidget *parent):
    SubcategoryWindow(parent) {
    displaySubcategories(categoryName);

    if (categoryName != "") {
        // Set the category name
        updateSubcategoryWindow->setCategoryname(categoryName);

        // When clicking the back button, it will jump to the category window
        fromCategoryWindow = true;
    }
}

SubcategoryWindow::~SubcategoryWindow() {
    delete ui;
    delete updateSubcategoryDialog;
    delete updateSubcategoryWindow;
    delete itemModel;
}

void SubcategoryWindow::displaySubcategories(const QString &categoryName) {
    // Get the local user's ID
    int userId = LocalUser::get()->getId();

    // Retrieve all subcategories from the database
    auto subcategoryRepository = Database::getInstance()->getSubcategoryRepository();
    QList<Subcategory*> subcategoryList;
    if (categoryName == "") {
        subcategoryList = subcategoryRepository.getAllByUserId(userId);
    } else {
        auto categoryRepository = Database::getInstance()->getCategoryRepository();
        QSharedPointer<Category> category(categoryRepository.getByUserIdAndName(userId, categoryName));
        if (!category.isNull()) {
            subcategoryList = subcategoryRepository.getAllByCategoryId(category->getId());
        }
    }

    // Table header
    itemModel->setHorizontalHeaderLabels(QStringList() << "Name" << "Category");

    // Table rows
    auto categoryRepository = Database::getInstance()->getCategoryRepository();
    QMap<int, QString> categoryNameMap;
    for (int row = 0; row < subcategoryList.size(); ++row) {
        QSharedPointer<Subcategory> subcategory(subcategoryList.at(row));
        unsigned int categoryId = subcategory->getCategoryId();
        QString categoryName = categoryNameMap.value(categoryId, "");
        if (categoryName == "") {
            QSharedPointer<Category> category(categoryRepository.get(categoryId));
            if (category == nullptr) {
                continue;
            }

            categoryName = category->getName();
            categoryNameMap.insert(categoryId, categoryName);
        }

        QString subcategoryName = subcategory->getName();

        itemModel->setItem(row, 0, new QStandardItem(subcategoryName));
        itemModel->setItem(row, 1, new QStandardItem(categoryName));
    }

    ui->subcategoryTable->setModel(itemModel);

    // On selected
    connect(ui->subcategoryTable->selectionModel(), &QItemSelectionModel::selectionChanged,
            this, &SubcategoryWindow::onItemSelected);

    // Delete category list
    subcategoryList.clear();
}

void SubcategoryWindow::onItemSelected(const QItemSelection &selected, const QItemSelection &deselected) {
    for (const QModelIndex &index : selected.indexes()) {
        selectedIndexes.insert(index.row());
    }

    for (const QModelIndex &index : deselected.indexes()) {
        selectedIndexes.remove(index.row());
    }
}

void SubcategoryWindow::onAddbuttonClicked() {
    // Check if there is categories
    if (updateSubcategoryWindow->getCategoryCount() == 0) {
        showStatusMessage("You haven't created any category yet.", "red");
        return;
    }

    updateIndex = -1;

    // Set the subcategory name
    updateSubcategoryWindow->setSubcategoryName("");

    updateSubcategoryDialog->setWindowTitle("Add Subcategory");
    updateSubcategoryDialog->exec();
}

void SubcategoryWindow::onUpdateButtonClicked() {
    if (selectedIndexes.isEmpty()) {
        return showStatusMessage("You must select a subcategory first!", "red");
    }

    if (selectedIndexes.size() > 1) {
        return showStatusMessage("You must select only one subcategory!", "red");
    }

    updateIndex = *selectedIndexes.begin();

    // Set the category name for the update window
    auto categoryName = itemModel->item(updateIndex, 1)->data(Qt::DisplayRole).toString();
    updateSubcategoryWindow->setCategoryname(categoryName);

    // Set the subcategory name
    auto subcategoryName = itemModel->item(updateIndex, 0)->data(Qt::DisplayRole).toString();
    updateSubcategoryWindow->setSubcategoryName(subcategoryName);

    updateSubcategoryDialog->setWindowTitle("Update Subcategory");
    updateSubcategoryDialog->exec();
}

void SubcategoryWindow::onDeleteButtonClicked() {
    // Check if no categories are selected
    if (selectedIndexes.isEmpty()) {
        showStatusMessage("No selected subcategories to delete..", "red");
    }

    // Confirm the deletion
    QString numSelectedSubcategory = QString::number(selectedIndexes.size());
    QString text = "Are you sure to delete the selected " + numSelectedSubcategory + " subcategories?";
    bool confirmed = WindowUtil::createConfirmationBox(this, text);
    if (!confirmed) {
        return;
    }

    // Get the local user's ID
    int userId = LocalUser::get()->getId();

    auto subcategoryRepository = Database::getInstance()->getSubcategoryRepository();
    auto categoryRepository = Database::getInstance()->getCategoryRepository();
    QList<int> deletedRows;
    for (QSet<int>::const_iterator it = selectedIndexes.constBegin(); it != selectedIndexes.constEnd(); ++it) {
        int row = *it;
        deletedRows.append(row);

        QString subcategoryName = itemModel->item(row, 0)->data(Qt::DisplayRole).toString();
        QString categoryName = itemModel->item(row, 1)->data(Qt::DisplayRole).toString();

        // Check if the category exists
        QSharedPointer<Category> category(categoryRepository.getByUserIdAndName(userId, categoryName));
        if (category.isNull()) {
            continue;
        }

        // Check if the subcategory exists
        QSharedPointer<Subcategory> subcategory(subcategoryRepository.getByUserIdAndCategoryIdAndName(
            userId, category->getId(), subcategoryName));
        if (subcategory.isNull()) {
            continue;
        }

        // Remove the subcategory
        SubcategoryService subcategoryService;
        subcategoryService.removeSubcategory(subcategory->getId());
    }

    // Remove the rows from the table view
    itemModel->removeRows(deletedRows.first(), deletedRows.size());

    // Show status message
    showStatusMessage("You deleted " + numSelectedSubcategory + " subcategories!", "green");
}

void SubcategoryWindow::onBackButtonClicked() {
    if (fromCategoryWindow) {
        WindowUtil::jump(this, new CategoryWindow);
    } else {
        WindowUtil::jump(this, new MainWindow);
    }
}

void SubcategoryWindow::onUpdateConfirmed(const QString &categoryName, const QString &subcategoryName) {
    // Close the dialog
    updateSubcategoryDialog->close();

    // If the subcategory name is an empty string, cut off the process
    if (categoryName =="" || subcategoryName == "") {
        return;
    }

    if (updateIndex == -1) {
        addSubcategory(categoryName, subcategoryName);
    } else {
        updateSubcategory(categoryName, subcategoryName);
    }
}

void SubcategoryWindow::addSubcategory(const QString &categoryName, const QString &subcategoryName) {
    // Get the local user's ID
    int userId = LocalUser::get()->getId();

    // Check whether the category exists
    auto categoryRepository = Database::getInstance()->getCategoryRepository();
    QSharedPointer<Category> category(categoryRepository.getByUserIdAndName(userId, categoryName));
    if (category.isNull()) {
        return WindowUtil::createErrorMessageBox(this, "The category has been deleted!");
    }

    // Check whether the subcategory exists
    auto subcategoryRepository = Database::getInstance()->getSubcategoryRepository();
    auto categoryId = category->getId();
    QSharedPointer<Subcategory> subcategory(
        subcategoryRepository.getByUserIdAndCategoryIdAndName(userId, categoryId, subcategoryName));
    if (!subcategory.isNull()) {
        return WindowUtil::createErrorMessageBox(this, "The subcategory already exists!");
    }

    // Create a subcategory
    QSharedPointer<Subcategory> newSubcategory(subcategoryRepository.create(userId, categoryId, subcategoryName));
    if (newSubcategory.isNull()) {
        return WindowUtil::createErrorMessageBox(this, "Fail to create the subcategory!");
    }

    // Append the subcatgory to the table
    setRow(itemModel->rowCount(), subcategoryName, category->getName());

    // Show status message
    showStatusMessage("You added an category successfully!", "green");
}

void SubcategoryWindow::updateSubcategory(const QString &categoryName, const QString &subcategoryName) {
    // Get the local user's ID
    int userId = LocalUser::get()->getId();

    // Get the original category
    QString originalCategoryName = itemModel->item(updateIndex, 1)->data(Qt::DisplayRole).toString();
    auto categoryRepository = Database::getInstance()->getCategoryRepository();
    QSharedPointer<Category> originalCategory(categoryRepository.getByUserIdAndName(userId, originalCategoryName));
    if (originalCategory.isNull()) {
        return WindowUtil::createErrorMessageBox(this, "The original category does not exist!");
    }

    // Get the subcategory
    QString originalSubcategoryName = itemModel->item(updateIndex, 0)->data(Qt::DisplayRole).toString();
    auto subcategoryRepository = Database::getInstance()->getSubcategoryRepository();
    QSharedPointer<Subcategory> subcategory(subcategoryRepository.getByUserIdAndCategoryIdAndName(
        userId, originalCategory ->getId(), originalSubcategoryName));
    if (subcategory.isNull()) {
        return WindowUtil::createErrorMessageBox(this, "The subcategory does not exist!");
    }

    // Check if new category exists; determine the new category id
    auto newCategoryId = originalCategory->getId();
    if (categoryName != originalCategory->getName()) {
        QSharedPointer<Category> category(categoryRepository.getByUserIdAndName(userId, categoryName));
        if (category.isNull()) {
            return WindowUtil::createErrorMessageBox(this, "The category does not exist!");
        }
        newCategoryId = category->getId();
    }

    // Update the subcategory
    bool updateResult = subcategoryRepository.update(subcategory->getId(), newCategoryId, subcategoryName);
    if (!updateResult) {
        qDebug() << "Fail to update the subcategory.";
    }

    // Update the row; reset the update index
    setRow(updateIndex, subcategoryName, categoryName);
    updateIndex = -1;

    // Show status message
    showStatusMessage("You updated the subcategory successfully!", "green");
}

void SubcategoryWindow::showStatusMessage(const QString &message, const QString &color) {
    ui->statusLabel->setStyleSheet("color:" + color + ";");
    ui->statusLabel->setText(message);
    TimerUtil::setTimeout(3000, [this]() {
        ui->statusLabel->setText("");
    });
}

void SubcategoryWindow::setRow(int row, const QString& subcategoryName, const QString &categoryName) {
    itemModel->setItem(row, 0, new QStandardItem(subcategoryName));
    itemModel->setItem(row, 1, new QStandardItem(categoryName));
}
