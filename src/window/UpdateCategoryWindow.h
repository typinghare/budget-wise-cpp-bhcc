#ifndef UPDATECATEGORYWINDOW_H
#define UPDATECATEGORYWINDOW_H

#include <QWidget>

namespace Ui { class UpdateCategoryWindow; }

class UpdateCategoryWindow : public QWidget {
    Q_OBJECT

public:
    explicit UpdateCategoryWindow(QWidget *parent = nullptr);
    ~UpdateCategoryWindow();

    /**
     * @brief Set the name of the category input.
     */
    void setCategoryName(const QString& categoryName);

signals:
    /**
     * @brief User confirms the category name.
     * @param categoryName the category name.
     */
    void categoryNameConfirmed(const QString& categoryName);

private slots:
    /**
     * @brief Closes this window; triggers the categoryNameConfirmed signal.
     */
    void onOkButtonClicked();

    /**
     * @brief Closes this window; triggers the categoryNameConfirmed signal.
     */
    void onCancelButtonClicked();

private:
    Ui::UpdateCategoryWindow *ui;
};

#endif // UPDATECATEGORYWINDOW_H
