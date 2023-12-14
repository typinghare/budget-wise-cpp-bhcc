#ifndef CATEGORYWINDOW_H
#define CATEGORYWINDOW_H

#include <QWidget>
#include <QDialog>
#include <QStandardItemModel>
#include <QItemSelection>

#include "UpdateCategoryWindow.h"

namespace Ui { class CategoryWindow; }

class CategoryWindow : public QWidget {
    Q_OBJECT

public:
    explicit CategoryWindow(QWidget *parent = nullptr);
    ~CategoryWindow();

    /**
     * @brief Retrieves categories from the database and display them.
     */
    void displayCategories();

    /**
     * @brief Shows a status messaage.
     */
    void showStatusMessage(const QString& message, const QString& color);

    /**
     * @brief Adds a category.
     * @param The name of the category.
     */
    void addCategory(const QString& categoryName);

    /**
     * @brief Updates a category.
     * @param The name of the category.
     */
    void updateCategory(const QString& categoryName);

public slots:
    /**
     * @brief Adds a new category.
     */
    void onAddButtonClicked();

    /**
     * @brief Updates selected category.
     */
    void onUpdateButtonClicked();

    /**
     * @brief Deletes selected category.
     */
    void deleteSelectedCategory();

    /**
     * @brief Jumps back to the main window.
     */
    void back();

    /**
     * @brief Triggered when the user confirms the category name.
     * @param categoryName The category name.
     */
    void onUpdateConfirmed(const QString& categoryName);

    /**
     * @brief Sets the selected indexes.
     */
    void onItemSelected(const QItemSelection &selected, const QItemSelection &deselected);

    /**
     * @brief Triggered when the table is double clicked.
     * @param index The index of the item.
     */
    void onTableDoubleClicked(const QModelIndex& index);

    /**
     * @brief onManageCategoriesButtonClicked
     */
    void onManageCategoriesButtonClicked();

    /**
     * @brief onRecordButtonClicked
     */
    void onRecordButtonClicked();

private:
    Ui::CategoryWindow *ui;
    QDialog *updateCategoryDialog;
    UpdateCategoryWindow *updateCategoryWindow;
    QStandardItemModel *itemModel;
    QSet<int> selectedIndexes;
    int updateIndex;

    bool checkSingleSelected();
};

#endif // CATEGORYWINDOW_H
