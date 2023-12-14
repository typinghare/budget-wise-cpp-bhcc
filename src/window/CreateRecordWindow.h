#ifndef CREATERECORDWINDOW_H
#define CREATERECORDWINDOW_H

#include <QWidget>
#include <QSharedPointer>
#include <QMap>

#include "src/entity/Subcategory.h"

namespace Ui { class CreateRecordWindow; }

class CreateRecordWindow : public QWidget {
    Q_OBJECT

public:
    explicit CreateRecordWindow(QWidget *parent = nullptr);
    ~CreateRecordWindow();

    /**
     * @brief Refreshes categories.
     */
    void refreshCategories();

    /**
     * @brief Returns the number of categories in the combo box.
     */
    int getCategoryCount();

    /**
     * @brief set the amount.
     * @param amount The amount.
     */
    void setAmount(double amount);

signals:
    /**
     * @brief User confirms the record.
     * @param categoryId The ID of the selected category.
     * @param subcategoryId The ID of the selected subcategory.
     * @param amount The amount of the money of the record.
     */
    void confirmed(unsigned int categoryId, unsigned int subcategoryId, double amount);

    /**
     * @brief Creation canceled.
     */
    void canceled();

public slots:
    /**
     * @brief Slot called when the "OK" button is clicked.
     */
    void onOkButtonClicked();

    /**
     * @brief Slot called when the "Cancel" button is clicked.
     */
    void onCancelButtonClicked();

    /**
     * @brief onComboBoxActivated
     * @param index
     */
    void onComboBoxActivated(int index);

private:
    Ui::CreateRecordWindow *ui;
    QMap<int, int> categoryIdMap;
    QMap<int, int> subcategoryIdMap;

    void loadSubcategories(unsigned int categoryId);
};

#endif // CREATERECORDWINDOW_H
