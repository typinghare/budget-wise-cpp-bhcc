#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QDialog>
#include <QStandardItemModel>
#include <QAction>

#include "UpdateCategoryWindow.h"
#include "CreateRecordWindow.h"

namespace Ui { class MainWindow; }

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    /**
     * @brief Create the menu.
     */
    void createMenu();

    /**
     * @brief Load subcategories and add them to the create record window.
     */
    void loadSubcategories();

    /**
     * @brief Loads and displays records.
     */
    void loadRecords();

    /**
     * @brief Loads user's current balance.
     */
    void loadCurrentBalance();

    /**
     * @brief Sets balance.
     * @param balance The balance to set.s
     */
    void setBalance(double balance);

public slots:
    /**
     * @brief Jumps to the category window.
     */
    void openCategoryWindow();

    /**
     * @brief Jumps to the subcategory window.
     */
    void openSubcategoryWindow();

    /**
     * @brief User logouts.
     */
    void logout();

    /**
     * @brief Slot called when the confirmed singal from the create record window is received.
     * @param subcategoryId The ID of the selected subcategory.
     * @param amount The amount of the new record.
     */
    void onCreateConfirmed(unsigned int categoryId, unsigned int subcategoryId, double amount);

    /**
     * @brief Slot called when the canceled singal from the create record window is received.
     */
    void onCreateCanceled();

    /**
     * @brief Opens create record window.
     */
    void onAddButtonClicked();

    /**
     * @brief Deletes the last record.
     */
    void onDeleteLastButtonClicked();

    /**
     * @brief onViewButtonClicked
     */
    void onViewButtonClicked();

private:
    Ui::MainWindow *ui;

    QAction *logoutActioin;

    QDialog *createRecordDialog;
    CreateRecordWindow *createRecordWindow;
    QStandardItemModel *itemModel;
    QMap<unsigned int, QString> categoryIdMap;          // category ID => category name
    QMap<unsigned int, QString> subcategoryIdMap;       // subcategory ID => subcategory name

    void setRow(
        int row,
        QDateTime createdAt,
        const QString& categoryName,
        const QString& subcategoryName,
        double amount,
        double balance
        );

    void unshiftRow(
        QDateTime createdAt,
        const QString& categoryName,
        const QString& subcategoryName,
        double amount,
        double balance
        );
};

#endif // MAINWINDOW_H
