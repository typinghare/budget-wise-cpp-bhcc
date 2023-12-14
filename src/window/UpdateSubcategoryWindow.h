#ifndef UPDATESUBCATEGORYWINDOW_H
#define UPDATESUBCATEGORYWINDOW_H

#include <QWidget>

namespace Ui { class UpdateSubcategoryWindow; }

class UpdateSubcategoryWindow : public QWidget {
    Q_OBJECT

public:
    explicit UpdateSubcategoryWindow(QWidget *parent = nullptr);
    ~UpdateSubcategoryWindow();

    /**
     * @brief Puts the category names into the combo box.
     * @param categoryList A list of category names.
     */
    void setCategoryNames(QList<QString> categoryNameList);

    /**
     * @brief Sets the category name.
     * @param categoryName The category name to set.
     */
    void setCategoryname(const QString &categoryName);

    /**
     * @brief Set the name of the subcategoryName input.
     */
    void setSubcategoryName(const QString& subcategoryName);

    /**
     * @brief Returns the number of the category.
     */
    int getCategoryCount();

signals:
    /**
     * @brief User confirms the category name and subcategory name.
     * @param categoryName The category name.
     * @param subcategoryName The subcategory name.
     */
    void confirmed(const QString& categoryName, const QString& subcategoryName);

private slots:
    /**
     * @brief Closes this window; triggers the subcategoryNameConfirmed signal.
     */
    void onOkButtonClicked();

    /**
     * @brief Closes this window; triggers the categoryNameConfirmed signal.
     */
    void onCancelButtonClicked();

private:
    Ui::UpdateSubcategoryWindow *ui;
};

#endif // UPDATESUBCATEGORYWINDOW_H
