#include "ViewWindow.h"
#include "ui_ViewWindow.h"

#include "src/utils.h"
#include "src/windows.h"
#include "src/Database.h"
#include "src/LocalUser.h"

ViewWindow::ViewWindow(QWidget *parent):
    QWidget(parent),
    ui(new Ui::ViewWindow),
    boxLayout(new QVBoxLayout()),
    chart(new QChart()),
    chartView(new QChartView(chart)),
    series(new QLineSeries()),
    axisX(new QBarCategoryAxis()),
    axisY(new QValueAxis) {
    ui->setupUi(this);

    // Title
    setWindowTitle("Insight - BudgetWise");

    // Events
    connect(ui->backButton, &QPushButton::clicked, this, &ViewWindow::onBackButtonClicked);
    connect(ui->resetButton, &QPushButton::clicked, this, &ViewWindow::onResetButtonClicked);
    connect(ui->okButton, &QPushButton::clicked, this, &ViewWindow::onOkButtonClicked);
    connect(ui->categoryCombo, QOverload<int>::of(&QComboBox::activated), this, &ViewWindow::onComboBoxActivated);

    loadCategories();

    initiateChart();
}

ViewWindow::~ViewWindow() {
    delete ui;
}

void ViewWindow::initiateChart() {
    // Axes
    chart->addAxis(axisX, Qt::AlignBottom);
    chart->addAxis(axisY, Qt::AlignLeft);
    axisX->setTitleText("Date (Month/Day/Year)");
    axisY->setTitleText("Amount (US dollars)");
    axisY->setLabelFormat("%d");
    axisX->setGridLineVisible(false);

    // Chart
    chart->addSeries(series);
    chartView->setRenderHint(QPainter::Antialiasing);

    // Attach the axes to the series
    series->attachAxis(axisX);
    series->attachAxis(axisY);

    // Set up layout
    ui->chartGroupBox->setLayout(boxLayout);
    boxLayout->addWidget(chartView);

    // Set the minimum size of the chartView
    chartView->setMinimumSize(ui->chartGroupBox->width(), ui->chartGroupBox->height());

    // Hide the legend
    chart->legend()->hide();

    // Hide the char view first
    chartView->hide();
}

void ViewWindow::onBackButtonClicked() {
    WindowUtil::jump(this, new MainWindow);
}

void ViewWindow::onOkButtonClicked() {
    // Get the category Id (>0)
    auto categoryComboInndex = ui->categoryCombo->currentIndex();
    auto categoryId = categoryIdMap[categoryComboInndex];

    // Get the subcategory Id (>=0)
    auto subcategoryComboInndex = ui->subcategoryCombo->currentIndex();
    auto subcategoryId = subcategoryIdMap[subcategoryComboInndex];

    // qDebug() << "category ID = " << categoryId << "; subcategory ID = " << subcategoryId;

    if (subcategoryId > 0) {
        return plotWithSubcategory(subcategoryId);
    } else if (categoryId > 0) {
        return plotWithCategory(categoryId);
    } else {
        return plot();
    }
}

void ViewWindow::onResetButtonClicked() {
    loadCategories();
}

void ViewWindow::onComboBoxActivated(int index) {
    int categoryId = categoryIdMap[index];
    QTimer::singleShot(0, this, [this, categoryId]() {
        loadSubcategories(categoryId);
    });
}

void ViewWindow::clearCategories() {
    // Clear all
    ui->categoryCombo->clear();
    categoryIdMap.clear();

    // no selected option
    ui->categoryCombo->addItem("(not selected)");
}

void ViewWindow::clearSubCategories() {
    // Clear all
    ui->subcategoryCombo->clear();
    subcategoryIdMap.clear();

    // no selected option
    ui->subcategoryCombo->addItem("(not selected)");
}

void ViewWindow::loadCategories() {
    clearCategories();

    auto userId = LocalUser::get()->getId();
    auto categoryRepository = Database::getInstance()->getCategoryRepository();
    auto categoryList = categoryRepository.getAll(userId);
    int index = 1;
    for (auto &category : categoryList) {
        auto categoryId = category->getId();
        auto categoryName = category->getName();
        categoryIdMap[index] = categoryId;
        ui->categoryCombo->addItem(categoryName);

        index++;
    }

    categoryList.clear();

    loadSubcategories(0);
}

void ViewWindow::loadSubcategories(unsigned int categoryId) {
    clearSubCategories();

    if (categoryId == 0) {
        return;
    }

    auto categoryComboInndex = ui->categoryCombo->currentIndex();
    auto catgoryId = categoryIdMap[categoryComboInndex];
    auto subcategoryRepository = Database::getInstance()->getSubcategoryRepository();
    auto subcategoryList = subcategoryRepository.getAllByCategoryId(catgoryId);
    int index = 1;
    for (auto &subcategory : subcategoryList) {
        auto subcategoryId = subcategory->getId();
        auto subcategoryName = subcategory->getName();
        subcategoryIdMap[index] = subcategoryId;
        ui->subcategoryCombo->addItem(subcategoryName);
        index++;
    }

    subcategoryList.clear();
}

void ViewWindow::plot() {
    // Get the records
    auto userId = LocalUser::get()->getId();
    auto recordRepository = Database::getInstance()->getRecordRepository();
    createChart(recordRepository.getAllByUser(userId, false));
}

void ViewWindow::plotWithCategory(unsigned int categoryId) {
    // Get the records
    auto recordRepository = Database::getInstance()->getRecordRepository();
    createChart(recordRepository.getAllByCategory(categoryId, false));
}

void ViewWindow::plotWithSubcategory(unsigned int subcategoryId) {
    // Get the records
    auto recordRepository = Database::getInstance()->getRecordRepository();
    createChart(recordRepository.getAllBySubcategory(subcategoryId, false));
}

void ViewWindow::createChart(QList<Record*> recordList) {
    if (recordList.size() > 8) {
        QList<Record*> lastEightRecords;
        for (int i = recordList.size() - 8; i < recordList.size(); ++i) {
            lastEightRecords.append(recordList[i]);
        }

        recordList.clear();
        recordList = lastEightRecords;
    }

    // Hide the chart view
    chartView->hide();

    // Nothing to plot
    if (recordList.size() == 0) {
        return;
    }

    // Prepare date string list
    QStringList dateStringList;
    QMap<int, int> valueMap;
    for (int index = 0; index < recordList.size(); ++index) {
        Record* record = recordList[index];
        valueMap[index] = record->getAmount();
        dateStringList << record->getCreatedAt().toString("MM/dd/yyyy");
    }

    // Determine the range
    double maxAmount = valueMap[0], minAmount = valueMap[1];
    for (auto it = valueMap.constBegin(); it != valueMap.constEnd(); ++it) {
        const int &value = it.value();
        if (value < minAmount) minAmount = value;
        if (value > maxAmount) maxAmount = value;
    }
    double gap = (maxAmount - minAmount) * 0.05 + 50;
    maxAmount += gap;
    minAmount -= gap;

    // Axes
    axisX->clear();
    axisX->append(dateStringList);
    axisX->setRange(dateStringList.first(), dateStringList.last());
    axisY->setRange(minAmount, maxAmount);

    // Set series
    series->clear();
    for (int index = 0; index < recordList.size(); ++index) {
        series->append(index, valueMap[index]);
    }

    // Repaint and show the chart view
    chartView->repaint();
    chartView->show();

    // Clear list
    recordList.clear();
}
