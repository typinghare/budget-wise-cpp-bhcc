#ifndef VIEWWINDOW_H
#define VIEWWINDOW_H

#include <QWidget>
#include <QMap>
#include <QLineSeries>
#include <QChart>
#include <QChartView>
#include <QVBoxLayout>
#include <QValueAxis>
#include <QBarCategoryAxis>

#include "src/entity/Record.h"

namespace Ui { class ViewWindow; }

class ViewWindow : public QWidget {
    Q_OBJECT

public:
    explicit ViewWindow(QWidget *parent = nullptr);
    ~ViewWindow();

public slots:
    /**
     * @brief Jumps back to the main window.
     */
    void onBackButtonClicked();

    /**
     * @brief Plots.
     */
    void onOkButtonClicked();

    /**
     * @brief Resets category combo box and subcategory combo box.
     */
    void onResetButtonClicked();

    /**
     * @brief onComboBoxActivated
     * @param index
     */
    void onComboBoxActivated(int index);

private:
    Ui::ViewWindow *ui;
    QMap<int, int> categoryIdMap;
    QMap<int, int> subcategoryIdMap;

    // Associated with charts
    QVBoxLayout *boxLayout;
    QChart *chart;
    QChartView *chartView;
    QLineSeries *series;
    QBarCategoryAxis *axisX;
    QValueAxis *axisY;

    void initiateChart();

    /**
     * @brief clearCategories
     */
    void clearCategories();

    /**
     * @brief clearSubCategories
     */
    void clearSubCategories();

    /**
     * @brief Loads categories.
     */
    void loadCategories();

    /**
     * @brief Loads subcategories.
     * @param categoryId The ID of the category.
     */
    void loadSubcategories(unsigned int categoryId);

    /**
     * @brief Plots all records.
     */
    void plot();

    /**
     * @brief Plots all records of a specific category.
     * @param categoryId The ID of the category.
     */
    void plotWithCategory(unsigned int categoryId);

    /**
     * @brief Plots all records of a specific subcategory.
     * @param subcategoryId The ID of the subcategory.
     */
    void plotWithSubcategory(unsigned int subcategoryId);

    /**
     * @brief Creates a chart.
     */
    void createChart(QList<Record*> recordList);
};

#endif // VIEWWINDOW_H
