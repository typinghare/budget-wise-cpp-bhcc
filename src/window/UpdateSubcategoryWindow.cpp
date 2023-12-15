#include "UpdateSubcategoryWindow.h"
#include "ui_UpdateSubcategoryWindow.h"

UpdateSubcategoryWindow::UpdateSubcategoryWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UpdateSubcategoryWindow) {
    ui->setupUi(this);

    // Events
    connect(ui->okButton, &QPushButton::clicked, this, &UpdateSubcategoryWindow::onOkButtonClicked);
    connect(ui->cancelButton, &QPushButton::clicked, this, &UpdateSubcategoryWindow::onCancelButtonClicked);
}

UpdateSubcategoryWindow::~UpdateSubcategoryWindow() {
    delete ui;
}

void UpdateSubcategoryWindow::setCategoryNames(QList<QString> categoryNameList) {
    for (const auto &categoryName: categoryNameList) {
        ui->categoryCombo->addItem(categoryName);
    }
}

void UpdateSubcategoryWindow::setCategoryname(const QString &categoryName) {
    int count = ui->categoryCombo->count();
    for (int index = 0; index < count; ++index) {
        if (ui->categoryCombo->itemText(index) == categoryName) {
            return ui->categoryCombo->setCurrentIndex(index);
        }
    }
}

int UpdateSubcategoryWindow::getCategoryCount() {
    return ui->categoryCombo->count();
}

void UpdateSubcategoryWindow::setSubcategoryName(const QString &subcategoryName) {
    ui->subcategoryNameInput->setText(subcategoryName);
}

void UpdateSubcategoryWindow::onOkButtonClicked() {
    QString categoryName = ui->categoryCombo->currentText();
    QString subcategoryName = ui->subcategoryNameInput->text();
    emit confirmed(categoryName, subcategoryName);
}

void UpdateSubcategoryWindow::onCancelButtonClicked() {
    setSubcategoryName("");
    emit confirmed("", "");
}
