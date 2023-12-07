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

public slots:
    /**
     * @brief Adds a new category.
     */
    void addCategory();

    /**
     * @brief Set the selected indexes.
     */
    void onItemSelected(const QItemSelection &selected, const QItemSelection &deselected);

    /**
     * @brief Updates selected category.
     */
    void updateSelectedCategory();

    /**
     * @brief Deletes selected category.
     */
    void deleteSelectedCategory();

    /**
     * @brief onCategoryNameConfirmed
     * @param categoryName The category name.
     */
    void onCategoryNameConfirmed(const QString& categoryName);

    /**
     * @brief Jumps back to the main window.
     */
    void back();

private:
    Ui::CategoryWindow *ui;
    QDialog *updateCategoryDialog;
    UpdateCategoryWindow *updateCategoryWindow;
    QStandardItemModel *itemModel;
    QSet<int> selectedIndexes;
};

#endif // CATEGORYWINDOW_H
