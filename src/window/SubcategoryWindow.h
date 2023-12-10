#ifndef SUBCATEGORYWINDOW_H
#define SUBCATEGORYWINDOW_H

#include <QWidget>
#include <QStandardItemModel>
#include <QItemSelection>

#include "UpdateSubcategoryWindow.h"

namespace Ui { class SubcategoryWindow; }

class SubcategoryWindow : public QWidget {
    Q_OBJECT

public:
    explicit SubcategoryWindow(QWidget *parent = nullptr);
    SubcategoryWindow(const QString& categoryName, QWidget *parent = nullptr);
    ~SubcategoryWindow();

    /**
     * @brief Shows a status messaage.
     */
    void showStatusMessage(const QString& message, const QString& color);

    /**
     * @brief Adds a subcategory.
     * @param categoryName The category name.
     * @param subcategoryName The subcategory name.
     */
    void addSubcategory(const QString &categoryName, const QString& subcategoryName);

    /**
     * @brief Updates a subcategory.
     * @param categoryName The category name.
     * @param subcategoryName The subcategory name.
     */
    void updateSubcategory(const QString &categoryName, const QString& subcategoryName);

public slots:
    /**
     * @brief Display subcategories.
     */
    void displaySubcategories(const QString &categoryName);

    /**
     * @brief Adds a subcategory.
     */
    void onAddbuttonClicked();

    /**
     * @brief Updates the selected subcategory.
     */
    void onUpdateButtonClicked();

    /**
     * @brief Deletes selected subcategories.
     */
    void onDeleteButtonClicked();

    /**
     * @brief Jumps back to the main window.
     */
    void onBackButtonClicked();

    /**
     * @brief Item selected event.
     */
    void onItemSelected(const QItemSelection &selected, const QItemSelection &deselected);

    /**
     * @brief Triggered when the user confirms at the update subcategory window.
     * @param categoryName The category name.
     * @param subcategoryName The subcategory name.
     */
    void onUpdateConfirmed(const QString &categoryName, const QString& subcategoryName);

private:
    Ui::SubcategoryWindow *ui;
    QDialog *updateSubcategoryDialog;
    UpdateSubcategoryWindow *updateSubcategoryWindow;
    QStandardItemModel *itemModel;
    QSet<int> selectedIndexes;
    int updateIndex;
    bool fromCategoryWindow;

    /**
     * @brief Sets a row.
     * @param row The number of row.
     */
    void setRow(int row, const QString& subcategoryName, const QString &categoryName);
};

#endif // SUBCATEGORYWINDOW_H
