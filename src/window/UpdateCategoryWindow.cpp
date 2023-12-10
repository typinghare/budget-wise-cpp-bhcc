#include "UpdateCategoryWindow.h"
#include "ui_UpdateCategoryWindow.h"

UpdateCategoryWindow::UpdateCategoryWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UpdateCategoryWindow) {
    ui->setupUi(this);

    // Events
    connect(ui->okButton, &QPushButton::clicked, this, &UpdateCategoryWindow::onOkButtonClicked);
    connect(ui->cancelButton, &QPushButton::clicked, this, &UpdateCategoryWindow::onCancelButtonClicked);
}

UpdateCategoryWindow::~UpdateCategoryWindow() {
    delete ui;
}

void UpdateCategoryWindow::setCategoryName(const QString& categoryName) {
    ui->categoryNameInput->setText(categoryName);
}

void UpdateCategoryWindow::onOkButtonClicked() {
    QString categoryName = ui->categoryNameInput->text();
    emit categoryNameConfirmed(categoryName);
}

void UpdateCategoryWindow::onCancelButtonClicked() {
    setCategoryName("");
    onOkButtonClicked();
}

