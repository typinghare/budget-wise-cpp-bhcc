#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui { class MainWindow; }

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void createMenu();

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

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
