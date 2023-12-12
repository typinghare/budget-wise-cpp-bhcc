#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QDialog>
#include <QStandardItemModel>
#include <QItemSelection>
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
     * @brief Loads and displays records.
     */
    void loadRecords();

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
    void onCreateConfirmed(unsigned int categoryId, float amount);

    /**
     * @brief Slot called when the canceled singal from the create record window is received.
     */
    void onCreateCanceled();

    /**
     * @brief Opens create record window.
     */
    void onAddButtonClicked();

private:
    Ui::MainWindow *ui;

    QAction *logoutActioin;

    QDialog *createRecordDialog;
    CreateRecordWindow *createRecordWindow;
    QStandardItem *itemModel;
};

#endif // MAINWINDOW_H
