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
     * @brief Puts the subcategory names into the combo box.
     * @param subcategoryList A list of subcategory names.
     */
    void setSubcategories(QList<Subcategory *> subcategoryList);

    /**
     * @brief Returns the number of subcategories in the combo box.
     */
    int getSubcategoryCount();

    /**
     * @brief set the amount.
     * @param amount The amount.
     */
    void setAmount(float amount);

signals:
    /**
     * @brief User confirms the record.
     * @param subcategoryId The ID of the selected subcategory.
     * @param amount The amount of the money of the record.
     */
    void confirmed(unsigned int subcategoryId, float amount);

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

private:
    Ui::CreateRecordWindow *ui;
    QMap<int, int> subcategoryIdMap;
};

#endif // CREATERECORDWINDOW_H
